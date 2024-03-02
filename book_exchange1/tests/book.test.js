const { expect } = require("chai");
const request = require("supertest");

const { Book } = require("../src/models");

const app = require("../src/app");

describe("/books", () => {
  // После каждого теста очищаем базу данных от записей книг
  afterEach(async () => {
    await Book.destroy({ where: {} });
  });

  describe("with no records in the database", () => {
    describe("POST /books", () => {
      it("creates a new book in the database", async () => {
        // Отправляем POST-запрос для создания новой книги
        const response = await request(app).post("/books").send({
          title: "The End",
          ISBN: "39393939",
        });
        // Получаем созданную запись книги из базы данных
        const newBookRecord = await Book.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(201);
        expect(response.body.title).to.equal("The End");
        expect(newBookRecord.ISBN).to.equal("39393939");
      });

      it("errors if title is null", async () => {
        // Отправляем POST-запрос с нулевым заголовком, ожидаем ошибку
        const response = await request(app).post("/books").send({
          title: null,
          ISBN: "39393939",
        });
        // Получаем созданную запись книги из базы данных
        const newBookRecord = await Book.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем, что сервер вернул ошибку и не создал запись в базе данных
        expect(response.status).to.equal(400);
        expect(response.body.errors.length).to.equal(1);
        expect(newBookRecord).to.equal(null);
      });
    });
  });

  describe("with records in the database", () => {
    let books;

    beforeEach(async () => {
      // Создаем три записи книг перед каждым тестом
      books = await Promise.all([
        Book.create({
          title: "The End",
          ISBN: "39393939",
        }),
        Book.create({
          title: "Rosi",
          ISBN: "39393940",
        }),
        Book.create({
          title: "Chati",
          ISBN: "39393941",
        }),
      ]);
    });

    describe("GET /books", () => {
      it("gets all books records", async () => {
        // Отправляем GET-запрос для получения всех записей книг
        const response = await request(app).get("/books");

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(response.body.length).to.equal(3);

        // Проверяем, что полученные данные совпадают с ожидаемыми
        response.body.forEach((book) => {
          const expected = books.find((a) => a.id === book.id);

          expect(book.title).to.equal(expected.title);
          expect(book.ISBN).to.equal(expected.ISBN);
        });
      });
    });

    describe("GET /books/:id", () => {
      it("gets books record by id", async () => {
        // Выбираем первую книгу из созданных записей
        const book = books[0];
        // Отправляем GET-запрос для получения записи книги по идентификатору
        const response = await request(app).get(`/books/${book.id}`);

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(response.body.title).to.equal(book.title);
        expect(response.body.ISBN).to.equal(book.ISBN);
      });

      it("returns a 404 if the book does not exist", async () => {
        // Отправляем GET-запрос для несуществующей книги
        const response = await request(app).get("/books/12345");

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The book could not be found.");
      });
    });

    describe("PATCH /books/:id", () => {
      it("updates books title by id", async () => {
        // Выбираем первую книгу из созданных записей
        const book = books[0];
        // Отправляем PATCH-запрос для обновления заголовка книги
        const response = await request(app)
          .patch(`/books/${book.id}`)
          .send({ title: "Nevermore" });
        // Получаем обновленную запись книги из базы данных
        const updatedBookRecord = await Book.findByPk(book.id, {
          raw: true,
        });

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(updatedBookRecord.title).to.equal("Nevermore");
      });

      it("returns a 404 if the book does not exist", async () => {
        // Отправляем PATCH-запрос для несуществующей книги
        const response = await request(app)
          .patch("/books/12345")
          .send({ title: "HeyHo" });

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The book could not be found.");
      });
    });

    describe("DELETE /books/:id", () => {
      it("deletes book record by id", async () => {
        // Выбираем первую книгу из созданных записей
        const book = books[0];
        // Отправляем DELETE-запрос для удаления записи книги
        const response = await request(app).delete(`/books/${book.id}`);
        // Пытаемся найти удаленную книгу в базе данных
        const deletedBook = await Book.findByPk(book.id, { raw: true });

        // Проверяем успешность операции и то, что книга была удалена
        expect(response.status).to.equal(204);
        expect(deletedBook).to.equal(null);
      });

      it("returns a 404 if the book does not exist", async () => {
        // Отправляем DELETE-запрос для несуществующей книги
        const response = await request(app).delete("/books/12345");
        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The book could not be found.");
      });
    });
  });
});
