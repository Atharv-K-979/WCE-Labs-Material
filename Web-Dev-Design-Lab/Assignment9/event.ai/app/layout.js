import { Geist, Geist_Mono } from "next/font/google";
import "./globals.css";
import { ThemeProvider } from "next-themes";
import Header from "../components/header";
import { ConvexClientProvider } from "./ClientClientProvider";
import { ClerkProvider } from "@clerk/nextjs";
import { dark } from "@clerk/themes";
import { Toaster } from "sonner";
export const metadata = {
  title: "event.AI",
  description: "Plan your event with AI",
};

export default function RootLayout({ children }) {
  return (
    <html lang="en" suppressHydrationWarning>
      <body
        className={`bg-linear-to-br from-gray-950 via-zinc-900 to-stone-900 text-white`}
        suppressHydrationWarning
      > <ThemeProvider
        attribute="class"
        defaultTheme="system"
        enableSystem
        disableTransitionOnChange
      >
          <ClerkProvider
            appearance={{
              theme: dark,
            }}>
            <ConvexClientProvider>

              {/* Header */}
              <Header />
              <main className="relative min-h-screen mx-auto pt-40 md:pt-32 max-w-7xl px-4 sm:px-6 lg:px-8">
                {/* glow */}
                <div className="pointer-events-none absolute inset-0 -z-10 overflow-hidden">
                  <div className="absolute left-1/4 top-0 w-96 h-96 bg-pink-600/20 rounded-full blur-3xl" />
                  <div className="absolute right-1/4 bottom-0 w-96 h-96 bg-orange-600/20 rounded-full blur-3xl" />
                </div>

                <div className="relative z-10 min-h-[70vh]">{children}</div>
                {/* Footer */}
                <footer className="border-t border-gray-800/50 py-8 px-6 max-w-7xl mx-auto">
                  <div className="text-sm text-gray-400">Made with ❤️ by  atharvk </div>
                </footer>
              </main>
              <Toaster richColors />
            </ConvexClientProvider>
          </ClerkProvider>
        </ThemeProvider>
      </body>
    </html>
  );
}
