import { AuthConfig } from "convex/server";

const authConfig = {
  providers: [
    {
      domain: "https://well-ladybug-54.clerk.accounts.dev",
      applicationID: "convex",
    },
  ]
};

export default authConfig;
