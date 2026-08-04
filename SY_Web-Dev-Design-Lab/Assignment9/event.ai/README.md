# 🚀 Event.ai

**Event.ai** is an AI-powered event planning and discovery platform designed to help users create, customize, discover, and manage events in a smart and intuitive way. 

By combining a modern SaaS user interface with real-time backend capabilities and AI-assisted workflows, Event.ai simplifies the entire event lifecycle—whether it’s a local meetup, professional workshop, concert, or tech talk.

---

## ✨ Key Features

### 🔐 Authentication & Users
* **Secure Access:** Powered by **Clerk** for seamless, secure authentication.
* **Onboarding:** Guided user onboarding and customizable profiles.
* **Session Handling:** Robust real-time session management.

### 📅 Event Creation
* **Rich Customization:** Add titles, descriptions, and categories.
* **Smart Scheduling:** Precise start/end date and time selection.
* **Location Intelligence:** State and city-based selection with specific venue details.
* **Visual Appeal:** Cover image uploads and dynamic theme color selection.
* **Flexible Access:** Support for both free and paid event structures.

### 🔍 Discovery Engine
* **Featured Events:** Highlighted events via a sleek carousel.
* **Proximity Search:** Discover events happening near your location.
* **Categorization:** Browse by interest (Tech, Music, Workshops, etc.).
* **Trending:** View popular events across different regions.

### 🎨 UI / UX
* **Modern Aesthetic:** Dark-themed SaaS design for a premium feel.
* **Fully Responsive:** Optimized experience across desktop, tablet, and mobile.
* **Atomic Components:** Built with reusable components and clean form logic.

---

## 🤖 AI Vision (In Progress)
Event.ai is evolving to include:
* ✨ **AI-Generated Descriptions:** Create compelling event copy in seconds.
* 🧠 **Smart Suggestions:** Automated category and timing recommendations.
* 🎯 **Smart Discovery:** Improved event ranking and location-based recommendations.

---

## 🛠️ Tech Stack

| Layer | Technology |
| :--- | :--- |
| **Frontend** | [Next.js](https://nextjs.org/) (App Router) |
| **Styling** | [Tailwind CSS](https://tailwindcss.com/) |
| **UI Components** | [shadcn/ui](https://ui.shadcn.com/) |
| **Backend** | [Convex](https://www.convex.dev/) (Real-time queries & mutations) |
| **Authentication** | [Clerk](https://clerk.com/) |
| **Icons** | [Lucide Icons](https://lucide.dev/) |

---

## 📂 Project Structure

```text
event.ai
├── app/                # Next.js App Router
├── components/         # UI components
│   ├── ui/             # shadcn base components
│   └── event-card.jsx  # Event display logic
├── convex/             # Backend (schema, queries, mutations)
├── lib/                # Utilities and constants
├── public/             # Static assets
└── README.md
```
---
## 🚀 Setup and Running Locally
Step 1: Clone the repository
```Bash
git clone [https://github.com/Atharv-K-979/event.ai.git](https://github.com/Atharv-K-979/event.ai.git)
cd event.ai
```
* **Step 2: Install dependencies
``` Bash
npm install
```
Step 3: Start Convex backend
```Bash
npx convex dev
```
Step 4: Start Next.js
```Bash
npm run dev
```
The application will be available at: http://localhost:3000

Environment Variables
Create a file named .env.local in the project root and add:
Code snippet
```Bash
# Deployment used by `npx convex dev`
CONVEX_DEPLOYMENT=

NEXT_PUBLIC_CONVEX_URL=

NEXT_PUBLIC_CLERK_PUBLISHABLE_KEY=
CLERK_SECRET_KEY=

NEXT_PUBLIC_CLERK_SIGN_IN_URL=/sign-in
NEXT_PUBLIC_CLERK_SIGN_UP_URL=/sign-up

CLERK_JWT_ISSUER_DOMAIN=

NEXT_PUBLIC_UNSPLASH_ACCESS_KEY=

GEMINI_API_KEY=
```
Note: For production, configure Convex environment variables through the Convex dashboard.

---

## 🛤️ Roadmap
[x] Core event creation flow

[x] Event discovery pages

[x] Authentication and user handling

[ ] AI-powered features (In Progress)

[ ] Payments and ticketing system (Planned)

---

## 🤝 Contributing
Contributions and improvements are welcome!
* Fork the repository.
* Create a new featurebranch (git checkout -b feature/AmazingFeature).
* Commit your changes.
* Open a Pull Request.

## Author: Atharv

### If you like this project, consider starring the repository on GitHub. Your support helps a lot! ⭐
