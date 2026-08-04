// import { useUser } from "@clerk/nextjs";
// import { useConvexAuth } from "convex/react";
// import { useEffect, useState } from "react";
// import { useMutation } from "convex/react";
// import { api } from "../convex/_generated/api";

// export function useStoreUserEffect() {
//   const { isLoading, isAuthenticated } = useConvexAuth();
//   const { user } = useUser();
//   // When this state is set we know the server
//   // has stored the user.
//   const [userId, setUserId] = useState(null);
//   const storeUser = useMutation(api.users.store);
//   // Call the `storeUser` mutation function to store
//   // the current user in the `users` table and return the `Id` value.
//   useEffect(() => {
//     // If the user is not logged in don't do anything
//     if (!isAuthenticated) {
//       return;
//     }
//     // Store the user in the database.
//     // Recall that `storeUser` gets the user information via the `auth`
//     // object on the server. You don't need to pass anything manually here.
//     async function createUser() {
//       const id = await storeUser();
//       setUserId(id);
//     }
//     createUser();
//     return () => setUserId(null);
//     // Make sure the effect reruns if the user logs in with
//     // a different identity
//   }, [isAuthenticated, storeUser, user?.id]);
//   // Combine the local state with the state from context
//   return {
//     isLoading: isLoading || (isAuthenticated && userId === null),
//     isAuthenticated: isAuthenticated && userId !== null,
//   };
// }


import { useUser } from "@clerk/nextjs";
import { useEffect, useState } from "react";
import { useMutation, useConvexAuth } from "convex/react";
import { api } from "../convex/_generated/api";

export function useStoreUserEffect() {
  const { user, isLoaded } = useUser();
  const storeUser = useMutation(api.users.store);
  const [stored, setStored] = useState(false);
  const { isAuthenticated } = useConvexAuth();

  useEffect(() => {
    // If not loaded, or no user, or already stored, do nothing.
    if (!isLoaded || !user || stored) return;

    // If loaded and user exists, but not authenticated with Convex yet, wait.
    if (!isAuthenticated) return;

    // Define async function to store user
    async function run() {
      try {
        await storeUser({
          tokenIdentifier: user.id,
          name: user.fullName ?? "Anonymous",
          email: user.primaryEmailAddress?.emailAddress,
          imageUrl: user.imageUrl,
        });
      } catch (error) {
        console.error("Error storing user:", error);
        // Even if it fails (e.g. unique constraint race constraint), 
        // we mark as stored to stop the spinner. 
        // The user likely exists or will be created next time.
      } finally {
        setStored(true);
      }
    }

    run();
  }, [isLoaded, user, isAuthenticated, stored, storeUser]);

  return {
    // Only show loading if Clerk is loaded, User exists, but we haven't finished "storing" (syncing) yet.
    isLoading: isLoaded && user !== null && !stored,
    isAuthenticated: !!user && stored,
  };
}
