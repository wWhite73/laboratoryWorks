const {
  createEntry,
  getAllEntries,
  getEntryById,
  updateEntry,
  deleteEntry,
  authenticateEntry,
} = require("./helper");

const readerCreate = (req, res) => createEntry(res, "reader", req.body, "email");

const readerGetAll = (_req, res) => getAllEntries(res, "reader");

const readerGetById = (req, res) => getEntryById(res, "reader", req.params.id);

const readerUpdate = (req, res) => updateEntry(res, "reader", req.params.id, req.body);

const readerDelete = (req, res) => deleteEntry(res, "reader", req.params.id);

const readerLogin = (req, res) => authenticateEntry(res, "reader", "email");

module.exports = {
  readerCreate,
  readerGetAll,
  readerGetById,
  readerUpdate,
  readerDelete,
  readerLogin,
};
