// import { defineSchema, defineTable } from "convex/server";
// import { v } from "convex/values";
// import { title } from "node:process";
// export default defineSchema({
//     //users tabkle
//     users: defineTable({
//         name: v.string(),
//         tokenIdentifier: v.string(), //clerk suer id for clerk auth
//         email: v.string(),
//         imageUrl: v.optional(v.string()),

//         //onboarding
//         hasCompletedOnboarding: v.boolean(),
//         location: v.optional(
//             v.object({
//                 city: v.string(),
//                 state: v.string(),
//                 country: v.string(),
//             })
//         ),
//         interests: v.optional(
//             v.array(v.string())
//         ),
//         freeEventsCreated: v.number(), // track free events created 1 free 
//         //timestamps
//         createdAt: v.number(),
//         updatedAt: v.number(),


//     }).index("by_token", ["tokenIdentifier"]),
//     events:defineTable({
//         title:v.string(),
//         description:v.string(),
//         slug:v.string(),

//         //Org
//         organizerId:v.id("users"),
//         organizerName:v.string(),

//         //Event details
//         category:v.string(),
//         tags:v.array(v.string()),

//         //Date and time
//         startDate:v.number(),
//         endDate:v.number(),
//         timezone:v.string(),

//         //Loc
//         locationType:v.union(v.literal("physical",v.literal("online"))),
//         venue:v.optional(v.string()),
//         address:v.optional(v.string()),
//         city:v.string(),
//         state:v.string(),
//         country:v.string(),

//         //
//     }),
//     registrations:defineTable({

//     })
// })



import { defineSchema, defineTable } from "convex/server";
import { v } from "convex/values";

export default defineSchema({
    // Users table
    users: defineTable({
        // Clerk auth
        email: v.string(),
        tokenIdentifier: v.string(), // Clerk user ID for auth
        name: v.string(),
        imageUrl: v.optional(v.string()),

        // Onboarding
        hasCompletedOnboarding: v.boolean(),

        // Loc
        location: v.optional(
            v.object({
                city: v.string(),
                state: v.optional(v.string()),
                country: v.string(),
            })
        ),
        interests: v.optional(v.array(v.string())), // Min 3 categories

        // Organizer tracking (User Subscription)
        freeEventsCreated: v.number(), // Track free event limit (1 free)

        // Time
        // createdAt: v.number(),
        // updatedAt: v.number(),
        createdAt: v.optional(v.float64()),
        updatedAt: v.optional(v.float64()),

    }).index("by_token", ["tokenIdentifier"]),

    // Events tab
    events: defineTable({
        title: v.string(),
        description: v.string(),
        slug: v.string(),

        // Org
        organizerId: v.id("users"),
        organizerName: v.string(),

        // Event details
        category: v.string(),
        tags: v.array(v.string()),

        // Date time
        startDate: v.number(),
        endDate: v.number(),
        timezone: v.string(),

        // Loc
        locationType: v.union(v.literal("physical"), v.literal("online")),
        venue: v.optional(v.string()),
        address: v.optional(v.string()),
        city: v.string(),
        state: v.optional(v.string()),
        country: v.string(),

        // Capacity & Ticketing
        capacity: v.number(),
        ticketType: v.union(v.literal("free"), v.literal("paid")),
        ticketPrice: v.optional(v.number()),
        registrationCount: v.number(),

        // Customization
        coverImage: v.optional(v.string()),
        themeColor: v.optional(v.string()),

        // Time
        createdAt: v.number(),
        updatedAt: v.number(),
    })
        .index("by_organizer", ["organizerId"])
        .index("by_category", ["category"])
        .index("by_start_date", ["startDate"])
        .index("by_slug", ["slug"])
        .searchIndex("search_title", { searchField: "title" }),

    // Registrations/Tickets
    registrations: defineTable({
        eventId: v.id("events"),
        userId: v.id("users"),

        // Attendee info
        attendeeName: v.string(),
        attendeeEmail: v.string(),

        // qr code
        qrCode: v.string(),

        // Check-in
        checkedIn: v.boolean(),
        checkedInAt: v.optional(v.number()),

        // Stat
        status: v.union(v.literal("confirmed"), v.literal("cancelled")),

        registeredAt: v.number(),
    })
        .index("by_event", ["eventId"])
        .index("by_user", ["userId"])
        .index("by_event_user", ["eventId", "userId"])
        .index("by_qr_code", ["qrCode"]),
});