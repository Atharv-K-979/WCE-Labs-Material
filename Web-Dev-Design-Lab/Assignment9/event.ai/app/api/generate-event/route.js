import { NextResponse } from "next/server";

export async function POST(req) {
    try {
        const { prompt } = await req.json();

        if (!prompt) {
            return NextResponse.json(
                { error: "Prompt is required" },
                { status: 400 }
            );
        }

        const apiKey = process.env.GEMINI_API_KEY;
        if (!apiKey) {
            console.error("Missing GEMINI_API_KEY in environment variables");
            return NextResponse.json(
                { error: "Server configuration error: Missing AI Key" },
                { status: 500 }
            );
        }

        // Call Gemini API directly via fetch to avoid adding dependencies
        const response = await fetch(
            `https://generativelanguage.googleapis.com/v1beta/models/gemini-1.5-flash:generateContent?key=${apiKey}`,
            {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({
                    contents: [
                        {
                            parts: [
                                {
                                    text: `
                    Generate a JSON object for an event based on this description: "${prompt}".
                    
                    The JSON must strictly follow this schema:
                    {
                      "title": "String",
                      "description": "String (engaging marketing description)",
                      "category": "String (one of: music, tech, sports, business, arts, social)",
                      "startDate": "ISO String (future date)",
                      "endDate": "ISO String (future date, shortly after start)",
                      "locationType": "String (physical or online)",
                      "city": "String (if physical, guess from context or default)",
                      "venue": "String (optional)",
                      "capacity": Number (guess from context),
                      "ticketType": "String (free or paid)",
                      "ticketPrice": Number (0 if free),
                      "tags": ["String", "String"]
                    }
                    
                    Return ONLY the JSON. Do not include markdown formatting like \`\`\`json.
                  `,
                                },
                            ],
                        },
                    ],
                }),
            }
        );

        const data = await response.json();

        if (!response.ok) {
            console.error("Gemini API Error:", data); // Log full error details
            throw new Error(data.error?.message || "Failed to fetch from Gemini");
        }

        let generatedText = data.candidates?.[0]?.content?.parts?.[0]?.text;

        if (!generatedText) {
            console.error("Gemini Response Missing Candidates:", data);
            throw new Error("No response from AI");
        }

        // Clean up potential markdown formatting
        generatedText = generatedText.replace(/```json/g, "").replace(/```/g, "").trim();

        const eventDetails = JSON.parse(generatedText);

        return NextResponse.json(eventDetails);

    } catch (error) {
        console.error("AI Generation Error:", error);
        return NextResponse.json(
            { error: error.message || "Failed to generate event details." },
            { status: 500 }
        );
    }
}
