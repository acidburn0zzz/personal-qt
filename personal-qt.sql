BEGIN TRANSACTION;

CREATE TABLE "Personal" ("Id" INTEGER PRIMARY KEY AUTOINCREMENT, "NIF" TEXT UNIQUE, "Nom" TEXT NOT NULL, "Codi" TEXT NOT NULL);

CREATE TABLE "Moviments" ("Id" INTEGER PRIMARY KEY AUTOINCREMENT, "Codi" TEXT, "Data" TEXT, "Hora" TEXT);

COMMIT;