const mongoose = require('mongoose');

const httpLogSchema = new mongoose.Schema({
  timestamp: { type: Date, default: Date.now },
  method: String,
  url: String,
  status: Number,
});

const dbLogSchema = new mongoose.Schema({
  timestamp: { type: Date, default: Date.now },
  operation: String,
});

const HttpLog = mongoose.model('HttpLog', httpLogSchema);
const DbLog = mongoose.model('DbLog', dbLogSchema);

module.exports = { HttpLog, DbLog };