"use client";

import { useParams } from "next/navigation";
import { useConvexQuery } from "../../../../hooks/use-convex-query";
import { api } from "../../../../convex/_generated/api";
import { Loader2, Calendar, MapPin, User, ArrowLeft, Share2 } from "lucide-react";
import { Button } from "../../../../components/ui/button";
import { Badge } from "../../../../components/ui/badge";
import Link from "next/link";
import Image from "next/image";
import { format } from "date-fns";
import { getCategoryIcon, getCategoryLabel } from "../../../../lib/data";

export default function EventDetailPage() {
    const params = useParams();
    const slug = params.slug;

    const { data: event, isLoading } = useConvexQuery(api.events.getEventBySlug, {
        slug: slug,
    });

    if (isLoading) {
        return (
            <div className="min-h-screen flex items-center justify-center">
                <Loader2 className="w-8 h-8 animate-spin text-purple-500" />
            </div>
        );
    }

    if (!event) {
        return (
            <div className="min-h-[60vh] flex flex-col items-center justify-center gap-4">
                <h1 className="text-2xl font-bold">Event not found</h1>
                <p className="text-muted-foreground">
                    The event you are looking for does not exist or has been removed.
                </p>
                <Button asChild variant="outline">
                    <Link href="/explore">Back to Explore</Link>
                </Button>
            </div>
        );
    }

    return (
        <div className="min-h-screen pb-20">
            {/* Back Button */}
            <div className="mb-6">
                <Button asChild variant="ghost" className="pl-0 hover:bg-transparent">
                    <Link href="/explore" className="flex items-center gap-2 text-muted-foreground hover:text-foreground">
                        <ArrowLeft className="w-4 h-4" />
                        Back to Explore
                    </Link>
                </Button>
            </div>

            <div className="grid grid-cols-1 lg:grid-cols-3 gap-8">
                {/* Main Content */}
                <div className="lg:col-span-2 space-y-8">
                    {/* Hero Image */}
                    <div className="aspect-video w-full rounded-2xl overflow-hidden relative border border-border/50 bg-muted">
                        {event.coverImage ? (
                            <Image
                                src={event.coverImage}
                                alt={event.title}
                                fill
                                className="object-cover"
                                priority
                            />
                        ) : (
                            <div
                                className="w-full h-full flex items-center justify-center text-6xl"
                                style={{ backgroundColor: event.themeColor }}
                            >
                                {getCategoryIcon(event.category)}
                            </div>
                        )}
                        <div className="absolute top-4 left-4">
                            <Badge className="bg-background/80 backdrop-blur-md text-foreground hover:bg-background/90">
                                {getCategoryLabel(event.category)}
                            </Badge>
                        </div>
                    </div>

                    {/* Details */}
                    <div>
                        <h1 className="text-3xl md:text-5xl font-bold mb-4">{event.title}</h1>

                        <div className="flex flex-wrap items-center gap-4 mb-8 text-muted-foreground">
                            <div className="flex items-center gap-2">
                                <Calendar className="w-4 h-4" />
                                <span>{format(event.startDate, "PPP p")}</span>
                            </div>
                            <div className="flex items-center gap-2">
                                <MapPin className="w-4 h-4" />
                                <span>
                                    {event.locationType === "online"
                                        ? "Online Event"
                                        : `${event.city}, ${event.state || event.country}`}
                                </span>
                            </div>
                            <div className="flex items-center gap-2">
                                <User className="w-4 h-4" />
                                <span>By {event.organizerName}</span>
                            </div>
                        </div>

                        <div className="prose prose-invert max-w-none">
                            <h3 className="text-xl font-semibold mb-3">About this event</h3>
                            <p className="whitespace-pre-wrap text-muted-foreground leading-relaxed">
                                {event.description}
                            </p>
                        </div>
                    </div>
                </div>

                {/* Sidebar Booking Card */}
                <div className="lg:col-span-1">
                    <div className="sticky top-24 rounded-xl border bg-card/50 backdrop-blur-sm p-6 space-y-6">
                        <div className="flex items-center justify-between">
                            <span className="text-sm font-medium text-muted-foreground">Price</span>
                            <span className="text-2xl font-bold">
                                {event.ticketType === "free" ? "Free" : `$${event.ticketPrice}`}
                            </span>
                        </div>

                        <div className="space-y-4">
                            <div className="flex justify-between text-sm">
                                <span className="text-muted-foreground">Spots remaining</span>
                                <span className="font-medium">
                                    {Math.max(0, event.capacity - event.registrationCount)} / {event.capacity}
                                </span>
                            </div>
                            <div className="w-full bg-secondary h-2 rounded-full overflow-hidden">
                                <div
                                    className="bg-purple-500 h-full transition-all"
                                    style={{ width: `${Math.min(100, (event.registrationCount / event.capacity) * 100)}%` }}
                                />
                            </div>
                        </div>

                        <Button className="w-full h-12 text-lg font-semibold bg-white text-black hover:bg-gray-200">
                            {event.ticketType === "free" ? "Register for Free" : "Get Tickets"}
                        </Button>

                        <div className="flex items-center justify-center gap-2 text-sm text-muted-foreground pt-2">
                            <Share2 className="w-4 h-4" />
                            Share this event
                        </div>
                    </div>
                </div>
            </div>
        </div>
    );
}
