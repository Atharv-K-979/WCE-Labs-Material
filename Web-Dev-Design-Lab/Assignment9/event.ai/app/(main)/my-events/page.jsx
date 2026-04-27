"use client";

import { useConvexQuery, useConvexMutation } from "../../../hooks/use-convex-query";
import { api } from "../../../convex/_generated/api";
import { useRouter } from "next/navigation";
import { Loader2, Calendar, MapPin, Trash2, Edit, Ticket } from "lucide-react";
import Image from "next/image";
import { format } from "date-fns";
import { Button } from "../../../components/ui/button";
import {
    AlertDialog,
    AlertDialogAction,
    AlertDialogCancel,
    AlertDialogContent,
    AlertDialogDescription,
    AlertDialogFooter,
    AlertDialogHeader,
    AlertDialogTitle,
    AlertDialogTrigger,
} from "../../../components/ui/alert-dialog";
import { toast } from "sonner";
import { useState } from "react";

export default function MyEventsPage() {
    const { data: events, isLoading } = useConvexQuery(api.events.getMyEvents);
    const { mutate: deleteEvent, isLoading: isDeleting } = useConvexMutation(api.events.deleteEvent);
    const router = useRouter();
    const [deletingId, setDeletingId] = useState(null);

    const handleDelete = async (eventId) => {
        setDeletingId(eventId);
        try {
            await deleteEvent({ eventId });
            toast.success("Event deleted successfully");
        } catch (error) {
            toast.error("Failed to delete event");
            console.error(error);
        } finally {
            setDeletingId(null);
        }
    };

    if (isLoading) {
        return (
            <div className="flex items-center justify-center min-h-[60vh]">
                <Loader2 className="w-8 h-8 animate-spin text-primary" />
            </div>
        );
    }

    return (
        <div className="max-w-6xl mx-auto px-6 py-8">
            <h1 className="text-3xl font-bold mb-8">My Events</h1>

            {events?.length === 0 ? (
                <div className="text-center py-20 bg-muted/30 rounded-xl border border-dashed">
                    <Calendar className="w-12 h-12 mx-auto text-muted-foreground mb-4" />
                    <h2 className="text-xl font-semibold">No events created yet</h2>
                    <p className="text-muted-foreground mt-2 mb-6">
                        Create your first event to get started managing them here.
                    </p>
                    <Button onClick={() => router.push("/create-event")}>
                        Create Event
                    </Button>
                </div>
            ) : (
                <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
                    {events?.map((event) => (
                        <div
                            key={event._id}
                            className="group relative bg-card rounded-xl border overflow-hidden hover:shadow-lg transition-all duration-300"
                        >
                            {/* Image */}
                            <div className="aspect-video relative bg-muted">
                                {event.coverImage ? (
                                    <Image
                                        src={event.coverImage}
                                        alt={event.title}
                                        fill
                                        className="object-cover"
                                    />
                                ) : (
                                    <div className="w-full h-full flex items-center justify-center bg-gradient-to-br from-primary/10 to-primary/5">
                                        <Calendar className="w-10 h-10 text-primary/40" />
                                    </div>
                                )}
                                <div className="absolute top-3 right-3 bg-black/50 backdrop-blur-md px-3 py-1 rounded-full text-xs font-medium text-white flex items-center gap-1.5">
                                    <Ticket className="w-3 h-3" />
                                    {event.ticketType === "free" ? "Free" : `₹${event.ticketPrice}`}
                                </div>
                            </div>

                            {/* Content */}
                            <div className="p-5">
                                <div className="flex justify-between items-start mb-2">
                                    <span className="text-xs font-medium text-primary bg-primary/10 px-2 py-1 rounded-md">
                                        {event.category}
                                    </span>
                                </div>

                                <h3 className="font-semibold text-xl mb-2 line-clamp-1 group-hover:text-primary transition-colors">
                                    {event.title}
                                </h3>

                                <div className="space-y-2 text-sm text-muted-foreground mb-4">
                                    <div className="flex items-center gap-2">
                                        <Calendar className="w-4 h-4" />
                                        <span>
                                            {format(new Date(event.startDate), "PPP")}
                                        </span>
                                    </div>
                                    <div className="flex items-center gap-2">
                                        <MapPin className="w-4 h-4" />
                                        <span className="line-clamp-1">
                                            {event.locationType === "online" ? "Online Event" : event.city || event.address}
                                        </span>
                                    </div>
                                </div>

                                {/* Actions */}
                                <div className="flex items-center gap-3 mt-4 pt-4 border-t">
                                    {/* <Button variant="outline" size="sm" className="flex-1 gap-2">
                                        <Edit className="w-4 h-4" />
                                        Edit
                                    </Button> */}

                                    <AlertDialog>
                                        <AlertDialogTrigger asChild>
                                            <Button
                                                variant="destructive"
                                                size="sm"
                                                className="flex-1 gap-2"
                                                disabled={deletingId === event._id}
                                            >
                                                {deletingId === event._id ? (
                                                    <Loader2 className="w-4 h-4 animate-spin" />
                                                ) : (
                                                    <Trash2 className="w-4 h-4" />
                                                )}
                                                Delete
                                            </Button>
                                        </AlertDialogTrigger>
                                        <AlertDialogContent>
                                            <AlertDialogHeader>
                                                <AlertDialogTitle>Delete Event?</AlertDialogTitle>
                                                <AlertDialogDescription>
                                                    This action cannot be undone. This will permanently delete the event
                                                    "{event.title}" and remove it from our servers.
                                                </AlertDialogDescription>
                                            </AlertDialogHeader>
                                            <AlertDialogFooter>
                                                <AlertDialogCancel>Cancel</AlertDialogCancel>
                                                <AlertDialogAction
                                                    onClick={() => handleDelete(event._id)}
                                                    className="bg-destructive hover:bg-destructive/90"
                                                >
                                                    Delete
                                                </AlertDialogAction>
                                            </AlertDialogFooter>
                                        </AlertDialogContent>
                                    </AlertDialog>
                                </div>
                            </div>
                        </div>
                    ))}
                </div>
            )}
        </div>
    );
}
