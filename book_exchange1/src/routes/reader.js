const express = require("express");
const router = express.Router();
const readerController = require("../controllers/reader");

router
  .route("/")
  .get(readerController.readerGetAll);

router
  .route("/:id")
  .get(readerController.readerGetById)
  .patch(readerController.readerUpdate)
  .delete(readerController.readerDelete);

router
  .route("/login")
  .post(readerController.readerLogin);

router
  .route("/registration")
  .post(readerController.readerCreate);

module.exports = router;
