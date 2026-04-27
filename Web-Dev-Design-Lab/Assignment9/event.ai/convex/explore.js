import { query } from "./_generated/server";
import { v } from "convex/values";

export const getFeaturedEvents = query({
  args: { limit: v.optional(v.number()) },
  handler: async (ctx, args) => {
    const limit = args.limit ?? 3;
    return await ctx.db.query("events").order("desc").take(limit);
  },
});

export const getEventsByLocation = query({
  args: {
    city: v.string(),
    state: v.optional(v.string()),
    limit: v.optional(v.number()),
  },
  handler: async (ctx, args) => {
    const limit = args.limit ?? 10;
    const results = await ctx.db
      .query("events")
      .filter((q) => q.eq(q.field("city"), args.city))
      .filter((q) =>
        args.state ? q.eq(q.field("state"), args.state) : q.eq(q.field("city"), args.city)
      )
      .order("desc")
      .take(limit);
    return results;
  },
});

export const getPopularEvents = query({
  args: { limit: v.optional(v.number()) },
  handler: async (ctx, args) => {
    const limit = args.limit ?? 6;
    const all = await ctx.db.query("events").collect();
    return all
      .sort((a, b) => (b.registrationCount ?? 0) - (a.registrationCount ?? 0))
      .slice(0, limit);
  },
});

export const getCategoryCounts = query({
  handler: async (ctx) => {
    const all = await ctx.db.query("events").collect();
    const counts = {};
    for (const e of all) {
      const key = e.category;
      counts[key] = (counts[key] ?? 0) + 1;
    }
    return counts;
  },
});

export const getEventsByCategory = query({
  args: { category: v.string(), limit: v.optional(v.number()) },
  handler: async (ctx, args) => {
    const limit = args.limit ?? 50;
    return await ctx.db
      .query("events")
      .withIndex("by_category", (q) => q.eq("category", args.category))
      .order("desc")
      .take(limit);
  },
});
