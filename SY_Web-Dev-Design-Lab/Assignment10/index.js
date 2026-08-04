// import express from "express";
// import dotenv from "dotenv";

// dotenv.config();

// const app = express();

// app.get("/", (req, res) => {
//   res.send("Application Deployed Successfully");
// });

// app.get("/status", (req, res) => {
//   res.json({
//     status: "running",
//     environment: process.env.NODE_ENV || "production"
//   });
// });

// const PORT = process.env.PORT || 5000;

// app.listen(PORT, "0.0.0.0", () => {
//   console.log(`Server running on port ${PORT}`);
// });



import express from "express";
import dotenv from "dotenv";

dotenv.config();

const app = express();

//Logging Middleware
app.use((req, res, next) => {
  const time = new Date().toISOString();
  console.log(`[${time}] ${req.method} ${req.url}`);
  next();
});

// Home
app.get("/", (req, res) => {
  res.send("Application Deployed Successfully");
});

// Status
app.get("/status", (req, res) => {
  res.json({
    status: "running",
    environment: process.env.NODE_ENV || "development"
  });
});

// Required: /info route
app.get("/info", (req, res) => {
  res.json({
    name: "Blog Application",
    version: "1.0.0",
    author: "Atharv Kulkarni"
  });
});

app.use((req, res) => {
  res.status(404).json({
    error: "Route not found"
  });
});

const PORT = process.env.PORT || 5000;

app.listen(PORT, "0.0.0.0", () => {
  console.log(`Server running in ${process.env.NODE_ENV} mode on port ${PORT}`);
});