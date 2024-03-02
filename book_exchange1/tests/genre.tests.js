const { expect } = require("chai");
const request = require("supertest");

const { Genre } = require("../src/models");

const app = require("../src/app");

describe("/genres", () => {
  // После каждого теста очищаем базу данных от записей жанров
  afterEach(async () => {
    await Genre.destroy({ where: {} });
  });

  describe("with no records in the database", () => {
    describe("POST /genres", () => {
      it("creates a new genre in the database", async () => {
        // Отправляем POST-запрос для создания нового жанра
        const response = await request(app).post("/genres").send({
          genre: "Horror",
        });
        // Получаем созданную запись жанра из базы данных
        const newGenreRecord = await Genre.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(201);
        expect(response.body.genre).to.equal("Horror");
        expect(newGenreRecord.genre).to.equal("Horror");
      });

      it("errors if genre is null", async () => {
        // Отправляем POST-запрос с нулевым жанром, ожидаем ошибку
        const response = await request(app).post("/genres").send({
          genre: null,
        });
        // Получаем созданную запись жанра из базы данных
        const newGenreRecord = await Genre.findByPk(response.body.id, {
          raw: true,
        });

        // Проверяем, что сервер вернул ошибку и не создал запись в базе данных
        expect(response.status).to.equal(400);
        expect(response.body.errors.length).to.equal(1);
        expect(newGenreRecord).to.equal(null);
      });
    });
  });

  describe("with records in the database", () => {
    let genres;

    beforeEach(async () => {
      // Создаем три записи жанров перед каждым тестом
      genres = await Promise.all([
        Genre.create({
          genre: "True Crime",
        }),
        Genre.create({
          genre: "Short Stories",
        }),
        Genre.create({
          genre: "Drama",
        }),
      ]);
    });

    describe("GET /genres", () => {
      it("gets all genres records", async () => {
        // Отправляем GET-запрос для получения всех записей жанров
        const response = await request(app).get("/genres");

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(response.body.length).to.equal(3);

        // Проверяем, что полученные данные совпадают с ожидаемыми
        response.body.forEach((genre) => {
          const expected = genres.find((a) => a.id === genre.id);

          expect(genre.genre).to.equal(expected.genre);
        });
      });
    });

    describe("GET /genres/:id", () => {
      it("gets genres record by id", async () => {
        // Выбираем первый жанр из созданных записей
        const genre = genres[0];
        // Отправляем GET-запрос для получения записи жанра по идентификатору
        const response = await request(app).get(`/genres/${genre.id}`);

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(response.body.genre).to.equal(genre.genre);
      });

      it("returns a 404 if the genre does not exist", async () => {
        // Отправляем GET-запрос для несуществующего жанра
        const response = await request(app).get("/genres/12345");

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The genre could not be found.");
      });
    });

    describe("PATCH /genres/:id", () => {
      it("updates genres genre by id", async () => {
        // Выбираем первый жанр из созданных записей
        const genre = genres[0];
        // Отправляем PATCH-запрос для обновления жанра по идентификатору
        const response = await request(app)
          .patch(`/genres/${genre.id}`)
          .send({ genre: "Self-Help" });
        // Получаем обновленную запись жанра из базы данных
        const updatedGenreRecord = await Genre.findByPk(genre.id, {
          raw: true,
        });

        // Проверяем успешность операции и соответствие данных
        expect(response.status).to.equal(200);
        expect(updatedGenreRecord.genre).to.equal("Self-Help");
      });

      it("returns a 404 if the genre does not exist", async () => {
        // Отправляем PATCH-запрос для несуществующего жанра
        const response = await request(app)
          .patch("/genres/12345")
          .send({ genre: "Romantic" });

        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The genre could not be found.");
      });
    });

    describe("DELETE /genres/:id", () => {
      it("deletes genre record by id", async () => {
        // Выбираем первый жанр из созданных записей
        const genre = genres[0];
        // Отправляем DELETE-запрос для удаления записи жанра
        const response = await request(app).delete(`/genres/${genre.id}`);
        // Пытаемся найти удаленный жанр в базе данных
        const deletedGenre = await Genre.findByPk(genre.id, { raw: true });

        // Проверяем успешность операции и то, что жанр был удален
        expect(response.status).to.equal(204);
        expect(deletedGenre).to.equal(null);
      });

      it("returns a 404 if the genre does not exist", async () => {
        // Отправляем DELETE-запрос для несуществующего жанра
        const response = await request(app).delete("/genres/12345");
        // Проверяем, что сервер вернул ошибку 404
        expect(response.status).to.equal(404);
        expect(response.body.error).to.equal("The genre could not be found.");
      });
    });
  });
});
