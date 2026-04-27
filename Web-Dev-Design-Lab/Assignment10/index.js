import express from "express";
import dotenv from "dotenv";

dotenv.config();

const app = express();

app.get("/", (req, res) => {
  res.send("Application Deployed Successfully");
});

app.get("/status", (req, res) => {
  res.json({
    status: "running",
    environment: process.env.NODE_ENV || "production"
  });
});

const PORT = process.env.PORT || 5000;

app.listen(PORT, "0.0.0.0", () => {
  console.log(`Server running on port ${PORT}`);
});
