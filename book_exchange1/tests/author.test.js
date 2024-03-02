const { expect } = require("chai");
const request = require("supertest");

const { Author } = require("../src/models");

const app = require("../src/app");

describe("/authors", () => {
  // После каждого теста очищаем базу данных от записей авторов
  afterEach(async () => {
    request(app);
    await Author.destroy({ where: {} });
  });

  describe("with no records in the database", () => {
    describe("POST /authors", () => {
      it("creates a new author in the database", async () => {
        // Отправляем POST-запрос для создания нового автора
        const response = await request(app).post("/authors").send({
          name: "Maribel",
        });
        // Получаем созданную запись автора из базы данных
        const newAuthorRecord = await Author.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(201);
        expect(response.body.name).to.equal("Maribel");
        expect(newAuthorRecord.name).to.equal("Maribel");
      });

      it("errors if name is null", async () => {
        // Отправляем POST-запрос с нулевым именем, ожидаем ошибку
        const response = await request(app).post("/authors").send({
          name: null,
        });
        // Получаем созданную запись автора из базы данных
        const newAuthorRecord = await Author.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем, что сервер вернул ошибку и не создал запись в базе данных
        expect(response.status).to.equal(400);
        expect(response.body.errors.length).to.equal(1);
        expect(newAuthorRecord).to.equal(null);
      });
    });
  });

  describe("with records in the database", () => {
    let authors;

    beforeEach(async () => {
      // Создаем три записи авторов перед каждым тестом
      authors = await Promise.all([
        Author.create({
          name: "Maribel",
        }),
        Author.create({
          name: "Rosi",
        }),
        Author.create({
          name: "Chati",
        }),
      ]);
    });

    describe("GET /authors", () => {
      it("gets all authors records", async () => {
        // Отправляем GET-запрос для получения всех записей авторов
        const response = await request(app).get("/authors");

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(response.body.length).to.equal(3);

        // Проверяем, что полученные данные совпадают с ожидаемыми
        response.body.forEach((author) => {
          const expected = authors.find((a) => a.id === author.id);
          expect(author.name).to.equal(expected.name);
        });
      });
    });

    describe("GET /authors/:id", () => {
      it("gets authors record by id", async () => {
        // Выбираем первого автора из созданных записей
        const author = authors[0];
        // Отправляем GET-запрос для получения записи автора по идентификатору
        const response = await request(app).get(`/authors/${author.id}`);

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(response.body.name).to.equal(author.name);
      });

      it("returns a 404 if the author does not exist", async () => {
        // Отправляем GET-запрос для несуществующего автора
        const response = await request(app).get("/authors/12345");

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The author could not be found.");
      });
    });

    describe("PATCH /authors/:id", () => {
      it("updates authors name by id", async () => {
        // Выбираем первого автора из созданных записей
        const author = authors[0];
        // Отправляем PATCH-запрос для обновления имени автора
        const response = await request(app)
          .patch(`/authors/${author.id}`)
          .send({ name: "Nevermore" });
        // Получаем обновленную запись автора из базы данных
        const updatedAuthorRecord = await Author.findByPk(author.id, {
          raw: true,
        });

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(updatedAuthorRecord.name).to.equal("Nevermore");
      });

      it("returns a 404 if the author does not exist", async () => {
        // Отправляем PATCH-запрос для несуществующего автора
        const response = await request(app)
          .patch("/authors/12345")
          .send({ title: "HeyHo" });

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The author could not be found.");
      });
    });

    describe("DELETE /authors/:id", () => {
      it("deletes author record by id", async () => {
        // Выбираем первого автора из созданных записей
        const author = authors[0];
        // Отправляем DELETE-запрос для удаления записи автора
        const response = await request(app).delete(`/authors/${author.id}`);
        // Пытаемся найти удаленного автора в базе данных
        const deletedAuthor = await Author.findByPk(author.id, { raw: true });

        // Проверяем успешность операции и то, что автор был удален
        expect(response.status).to.equal(204);
        expect(deletedAuthor).to.equal(null);
      });

      it("returns a 404 if the author does not exist", async () => {
        // Отправляем DELETE-запрос для несуществующего автора
        const response = await request(app).delete("/authors/12345");

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The author could not be found.");
      });
    });
  });
});
