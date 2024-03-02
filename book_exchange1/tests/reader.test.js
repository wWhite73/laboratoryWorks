const { expect } = require("chai");
const request = require("supertest");

const { Reader } = require("../src/models");

const app = require("../src/app");

describe("/readers", () => {
  // После каждого теста очищаем базу данных от записей читателей
  afterEach(async () => {
    await Reader.destroy({ where: {} });
  });

  describe("with no records in the database", () => {
    describe("POST /readers", () => {
      it("creates a new reader in the database", async () => {
        // Отправляем POST-запрос для создания нового читателя
        const response = await request(app).post("/readers").send({
          name: "Elizabeth Bennet",
          email: "future_ms_darcy@gmail.com",
          password: "sieteochonueve",
        });
        // Получаем созданную запись читателя из базы данных
        const newReaderRecord = await Reader.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(201);
        expect(response.body.name).to.equal("Elizabeth Bennet");
        // Проверяем, что пароль не возвращается в ответе
        expect(response.body.password).to.equal(undefined);
        expect(newReaderRecord.name).to.equal("Elizabeth Bennet");
        expect(newReaderRecord.email).to.equal("future_ms_darcy@gmail.com");
      });

      it("errors if email format not valid", async () => {
        // Отправляем POST-запрос с некорректным форматом email
        const response = await request(app).post("/readers").send({
          name: "Mariah Carey",
          email: "allIwantforXmasgmail.com",
          password: "sieteochonueve",
        });
        // Получаем созданную запись читателя из базы данных
        const newReaderRecord = await Reader.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем, что сервер вернул ошибку и не создал запись в базе данных
        expect(response.status).to.equal(400);
        expect(response.body.errors.length).to.equal(1);
        expect(newReaderRecord).to.equal(null);
      });

      it("errors if any fields are missing", async () => {
        // Отправляем POST-запрос с отсутствующими полями
        const response = await request(app).post("/readers").send({
          name: "",
          email: "",
          password: "",
        });
        // Получаем созданную запись читателя из базы данных
        const newReaderRecord = await Reader.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем, что сервер вернул ошибку и не создал запись в базе данных
        expect(response.status).to.equal(400);
        expect(response.body.errors.length).to.equal(3);
        expect(newReaderRecord).to.equal(null);
      });

      it("errors password is less than 8 char length", async () => {
        // Отправляем POST-запрос с коротким паролем
        const response = await request(app).post("/readers").send({
          name: "Mariah Carey",
          email: "alliwantforxmas@gmail.com",
          password: "siete",
        });
        // Получаем созданную запись читателя из базы данных
        const newReaderRecord = await Reader.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем, что сервер вернул ошибку и не создал запись в базе данных
        expect(response.status).to.equal(400);
        expect(response.body.errors.length).to.equal(1);
        expect(newReaderRecord).to.equal(null);
      });
    });
  });

  describe("with records in the database", () => {
    let readers;

    beforeEach(async () => {
      // Создаем три записи читателей перед каждым тестом
      readers = await Promise.all([
        Reader.create({
          name: "Omnius",
          email: "future_machine_lord@gmail.com",
          password: "sieteochonueve",
        }),
        Reader.create({
          name: "Hoques",
          email: "holdtherequest@gmail.com",
          password: "sieteochonueve",
        }),
        Reader.create({
          name: "Lyra Goldentongue",
          email: "ilovenorthernlights@gmail.com",
          password: "sieteochonueve",
        }),
      ]);
    });

    describe("GET /readers", () => {
      it("gets all readers records", async () => {
        // Отправляем GET-запрос для получения всех записей читателей
        const response = await request(app).get("/readers");

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(response.body.length).to.equal(3);

        // Проверяем, что полученные данные совпадают с ожидаемыми
        response.body.forEach((reader) => {
          const expected = readers.find((a) => a.id === reader.id);

          expect(reader.name).to.equal(expected.name);
          expect(reader.email).to.equal(expected.email);
          // Проверяем, что пароль не возвращается в ответе
          expect(reader.password).to.equal(undefined);
        });
      });
    });

    describe("GET /readers/:id", () => {
      it("gets readers record by id", async () => {
        // Выбираем первого читателя из созданных записей
        const reader = readers[0];
        // Отправляем GET-запрос для получения записи читателя по идентификатору
        const response = await request(app).get(`/readers/${reader.id}`);

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(response.body.name).to.equal(reader.name);
        expect(response.body.email).to.equal(reader.email);
        // Проверяем, что пароль не возвращается в ответе
        expect(response.body.password).to.equal(undefined);
      });

      it("returns a 404 if the reader does not exist", async () => {
        // Отправляем GET-запрос для несуществующего читателя
        const response = await request(app).get("/readers/12345");

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The reader could not be found.");
      });
    });

    describe("PATCH /readers/:id", () => {
      it("updates readers email by id", async () => {
        // Выбираем первого читателя из созданных записей
        const reader = readers[0];
        // Отправляем PATCH-запрос для обновления email у читателя
        const response = await request(app)
          .patch(`/readers/${reader.id}`)
          .send({ email: "erasmus@gmail.com" });
        // Получаем обновленную запись читателя из базы данных
        const updatedReaderRecord = await Reader.findByPk(reader.id, {
          raw: true,
        });

        // Проверяем успешность операции и соответствие обновленных данных
        expect(response.status).to.equal(200);
        expect(updatedReaderRecord.email).to.equal("erasmus@gmail.com");
      });

      it("returns a 404 if the reader does not exist", async () => {
        // Отправляем PATCH-запрос для несуществующего читателя
        const response = await request(app)
          .patch("/readers/12345")
          .send({ email: "xerxes@gmail.com" });

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The reader could not be found.");
      });
    });

    describe("DELETE /readers/:id", () => {
      it("deletes reader record by id", async () => {
        // Выбираем первого читателя из созданных записей
        const reader = readers[0];
        // Отправляем DELETE-запрос для удаления читателя
        const response = await request(app).delete(`/readers/${reader.id}`);
        // Пытаемся получить удаленную запись читателя из базы данных
        const deletedReader = await Reader.findByPk(reader.id, { raw: true });

        // Проверяем успешность операции и отсутствие записи в базе данных
        expect(response.status).to.equal(204);
        expect(deletedReader).to.equal(null);
      });

      it("returns a 404 if the reader does not exist", async () => {
        // Отправляем DELETE-запрос для несуществующего читателя
        const response = await request(app).delete("/readers/12345");
        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The reader could not be found.");
      });
    });
  });
});
