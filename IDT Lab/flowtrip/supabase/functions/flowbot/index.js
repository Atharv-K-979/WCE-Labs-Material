import { serve } from "https://deno.land/std@0.224.0/http/server";

const corsHeaders = {
  "Access-Control-Allow-Origin": "*",
  "Access-Control-Allow-Headers": "authorization, x-client-info, apikey, content-type, x-supabase-client-platform, x-supabase-client-platform-version, x-supabase-client-runtime, x-supabase-client-runtime-version",
};

function cleanMessages(value) {
  if (!Array.isArray(value)) return [];
  return value
    .filter((message): message is ChatMessage => {
      if (!message || typeof message !== "object") return false;
      const item = message;
      return (item.role === "user" || item.role === "assistant") && typeof item.content === "string" && item.content.trim().length > 0;
    })
    .slice(-8)
    .map((message) => ({ role: message.role, content: message.content.slice(0, 1200) }));
}

serve(async (req) => {
  if (req.method === "OPTIONS") return new Response(null, { headers: corsHeaders });

  try {
    const { messages } = await req.json();
    const cleanedMessages = cleanMessages(messages);
    const latest = cleanedMessages.at(-1)?.content ?? "";

    if (!latest.trim()) {
      return new Response(JSON.stringify({ error: "Ask FlowBot something first." }), {
        status: 400,
        headers: { ...corsHeaders, "Content-Type": "application/json" },
      });
    }

    const apiKey = Deno.env.get("LOVABLE_API_KEY") ?? Deno.env.get("GEMINI_API_KEY");
    if (!apiKey) throw new Error("FlowBot AI key is not configured");

    const response = await fetch("https://ai.gateway.lovable.dev/v1/chat/completions", {
      method: "POST",
      headers: {
        Authorization: `Bearer ${apiKey}`,
        "Content-Type": "application/json",
      },
      body: JSON.stringify({
        model: "google/gemini-3-flash-preview",
        messages: [
          {
            role: "system",
            content:
              "You are FlowBot, FlowTrip's India smart mobility assistant. Help users plan Indian journeys, explain route options, costs, reliability, CO2, buses, trains, autos, walking links, and map behavior. Be concise, friendly, and practical.",
          },
          ...cleanedMessages,
        ],
      }),
    });

    if (!response.ok) {
      if (response.status === 429) return new Response(JSON.stringify({ error: "FlowBot is busy. Try again in a moment." }), { status: 429, headers: { ...corsHeaders, "Content-Type": "application/json" } });
      if (response.status === 402) return new Response(JSON.stringify({ error: "FlowBot AI credits need attention in workspace usage." }), { status: 402, headers: { ...corsHeaders, "Content-Type": "application/json" } });
      const detail = await response.text();
      throw new Error(`FlowBot gateway error ${response.status}: ${detail}`);
    }

    const data = await response.json();
    const reply = data.choices?.[0]?.message?.content ?? "I can help with your FlowTrip journey. Try asking about Sangli to Mumbai.";

    return new Response(JSON.stringify({ reply }), {
      headers: { ...corsHeaders, "Content-Type": "application/json" },
    });
  } catch (error) {
    const message = error instanceof Error ? error.message : "FlowBot failed to respond";
    return new Response(JSON.stringify({ error: message }), {
      status: 500,
      headers: { ...corsHeaders, "Content-Type": "application/json" },
    });
  }
});
