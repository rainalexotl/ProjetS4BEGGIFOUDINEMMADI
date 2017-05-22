--Please see DataBase.java file for insert examples

DROP TABLE Game;
DROP TABLE Player;

------------------------------------------------------------
--Table: Player
------------------------------------------------------------

CREATE TABLE Player(
        alias VARCHAR2(30),
        email VARCHAR2(30),
        dateOfBirth DATE,
        nbWins NUMBER,
        nbForfeits NUMBER,
        CONSTRAINT pk_alias PRIMARY KEY (alias),
        CONSTRAINT ck_alias CHECK (alias IS NOT NULL),
        CONSTRAINT ck_email CHECK (email IS NOT NULL),
        CONSTRAINT ck_dob CHECK (dateOfBirth IS NOT NULL),
        CONSTRAINT ck_nbW CHECK (nbWins >= 0),
        CONSTRAINT ck_nbF CHECK (nbForfeits >= 0)
);


------------------------------------------------------------
--Table: Game
------------------------------------------------------------

CREATE TABLE Game(
        idGame NUMBER,
        nameGame VARCHAR2(30),
        startMove NUMBER,
        startDate DATE,
        blackPlayer VARCHAR2(30),
        whitePlayer VARCHAR2(30),
        CONSTRAINT pk_game PRIMARY KEY (idGame),
        CONSTRAINT fk_game_bp FOREIGN KEY (blackPlayer) REFERENCES Player (alias),
        CONSTRAINT fk_game_wp FOREIGN KEY (whitePlayer) REFERENCES Player (alias),
        CONSTRAINT ck_startMv CHECK (startMove >= 0),
        CONSTRAINT ck_startDt CHECK (startDate IS NOT NULL)
);