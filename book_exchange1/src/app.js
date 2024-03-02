const express = require("express");
const cors = require('cors');

const swaggerUi = require('swagger-ui-express');
const swaggerDoc = require('../swagger-output.json')

const mongoose = require('mongoose');
const morgan = require('morgan');

const readerRouter = require("./routes/reader");
const bookRouter = require("./routes/book");
const authorRouter = require("./routes/author");
const genreRouter = require("./routes/genre");

const app = express();

app.use(express.json()); 
app.use(cors());


mongoose.connect("mongodb://127.0.0.1:27017/bookrev_logs");

const httpLogSchema = new mongoose.Schema({
    method: String,
    url: String,
    status: Number,
    timestamp: { type: Date, default: Date.now },
  });
  
  const HttpLog = mongoose.model('HttpLog', httpLogSchema);
  
  app.use((req, res, next) => {
    const logEntry = new HttpLog({
      method: req.method,
      url: req.originalUrl,
      status: res.statusCode,
    });
  
    logEntry.save()
      .then(() => next())
      .catch(error => {
        console.error("Error logging to database:", error);
        next(error);
      });
  });
  
app.use(morgan('dev'));

app.use('/api-docs', swaggerUi.serve, swaggerUi.setup(swaggerDoc));

app.use("/readers", readerRouter);
app.use("/books", bookRouter);
app.use("/authors", authorRouter);
app.use("/genres", genreRouter);

module.exports = app;
