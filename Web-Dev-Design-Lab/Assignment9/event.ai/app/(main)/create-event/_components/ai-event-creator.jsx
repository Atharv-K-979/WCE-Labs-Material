"use client";

import { useState, useEffect } from "react";
import { Button } from "../../../../components/ui/button";
import { Input } from "../../../../components/ui/input";
import {
    Dialog,
    DialogContent,
    DialogDescription,
    DialogHeader,
    DialogTitle,
    DialogTrigger,
} from "../../../../components/ui/dialog";
import { Loader2, Sparkles } from "lucide-react";

export default function AIEventCreator({ onEventGenerated }) {
    const [mounted, setMounted] = useState(false);

    useEffect(() => {
        setMounted(true);
    }, []);

    const [open, setOpen] = useState(false);
    const [prompt, setPrompt] = useState("");
    const [isGenerating, setIsGenerating] = useState(false);

    if (!mounted) {
        return null;
    }

    const handleGenerate = async () => {
        if (!prompt) return;
        setIsGenerating(true);

        // TODO: Connect to actual AI endpoint (e.g. Convex action with OpenAI)
        // For now, mockup delay and specific response
        setTimeout(() => {
            const mockEvent = {
                title: `AI Generated: ${prompt}`,
                description: `This is an auto-generated description for "${prompt}". It includes detailed information about the schedule, speakers, and venue highlights to attract attendees. Join us for an unforgettable experience!`,
                category: "music", // Default to music or random
                suggestedCapacity: 100,
                suggestedTicketType: "free",
            };

            onEventGenerated(mockEvent);
            setIsGenerating(false);
            setOpen(false);
            setPrompt("");
        }, 1500);
    };

    return (
        <Dialog open={open} onOpenChange={setOpen}>
            <DialogTrigger asChild>
                <Button variant="outline" className="gap-2 border-purple-200 hover:bg-purple-50 hover:text-purple-600">
                    <Sparkles className="w-4 h-4 text-purple-500" />
                    Create with AI
                </Button>
            </DialogTrigger>
            <DialogContent className="sm:max-w-[425px]">
                <DialogHeader>
                    <DialogTitle className="flex items-center gap-2">
                        <Sparkles className="w-5 h-5 text-purple-500" />
                        AI Event Assistant
                    </DialogTitle>
                    <DialogDescription>
                        Describe your event idea, and let AI fill in the details.
                    </DialogDescription>
                </DialogHeader>
                <div className="grid gap-4 py-4">
                    <Input
                        placeholder="e.g., Tech meetup in Bangalore next weekend"
                        value={prompt}
                        onChange={(e) => setPrompt(e.target.value)}
                        disabled={isGenerating}
                    />
                    <Button onClick={handleGenerate} disabled={!prompt || isGenerating}>
                        {isGenerating ? (
                            <>
                                <Loader2 className="mr-2 h-4 w-4 animate-spin" />
                                Generating...
                            </>
                        ) : (
                            "Generate Details"
                        )}
                    </Button>
                </div>
            </DialogContent>
        </Dialog>
    );
}

// "use client";

// import { useState } from "react";
// import { Sparkles, Loader2 } from "lucide-react";
// import { Button } from "../../../../components/ui/button";
// import { Textarea } from "../../../../components/ui/textarea";
// import {
//     Dialog,
//     DialogContent,
//     DialogDescription,
//     DialogHeader,
//     DialogTitle,
//     DialogTrigger,
// } from "../../../../components/ui/dialog";
// import { toast } from "sonner";

// export default function AIEventCreator({ onEventGenerated }) {
//     const [isOpen, setIsOpen] = useState(false);
//     const [prompt, setPrompt] = useState("");
//     const [loading, setLoading] = useState(false);

//     const generateEvent = async () => {
//         if (!prompt.trim()) {
//             toast.error("Please describe your event");
//             return;
//         }

//         setLoading(true);
//         try {
//             const response = await fetch("/api/generate-event", {
//                 method: "POST",
//                 headers: { "Content-Type": "application/json" },
//                 body: JSON.stringify({ prompt }),
//             });

//             const data = await response.json();

//             if (!response.ok) {
//                 throw new Error(data.error || "Failed to generate event");
//             }

//             onEventGenerated(data);
//             toast.success("Event details generated! Review and customize below.");
//             setIsOpen(false);
//             setPrompt("");
//         } catch (error) {
//             toast.error("Failed to generate event. Please try again.");
//             console.error(error);
//         } finally {
//             setLoading(false);
//         }
//     };

//     return (
//         <Dialog open={isOpen} onOpenChange={setIsOpen}>
//             <DialogTrigger asChild>
//                 <Button variant="outline" className="gap-2">
//                     <Sparkles className="w-4 h-4" />
//                     Generate with AI
//                 </Button>
//             </DialogTrigger>
//             <DialogContent>
//                 <DialogHeader>
//                     <DialogTitle className="flex items-center gap-2">
//                         <Sparkles className="w-5 h-5 text-purple-500" />
//                         AI Event Creator
//                     </DialogTitle>
//                     <DialogDescription>
//                         Describe your event idea and let AI create the details for you
//                     </DialogDescription>
//                 </DialogHeader>

//                 <div className="space-y-4">
//                     <Textarea
//                         value={prompt}
//                         onChange={(e) => setPrompt(e.target.value)}
//                         placeholder="Example: A tech meetup about React 19 for developers in Bangalore. It should cover new features like Actions and use hook improvements..."
//                         rows={6}
//                         className="resize-none"
//                     />

//                     <div className="flex gap-2">
//                         <Button
//                             variant="outline"
//                             onClick={() => setIsOpen(false)}
//                             className="flex-1"
//                         >
//                             Cancel
//                         </Button>
//                         <Button
//                             onClick={generateEvent}
//                             disabled={loading || !prompt.trim()}
//                             className="flex-1 gap-2"
//                         >
//                             {loading ? (
//                                 <>
//                                     <Loader2 className="w-4 h-4 animate-spin" />
//                                     Generating...
//                                 </>
//                             ) : (
//                                 <>
//                                     <Sparkles className="w-4 h-4" />
//                                     Generate
//                                 </>
//                             )}
//                         </Button>
//                     </div>
//                 </div>
//             </DialogContent>
//         </Dialog>
//     );
// }