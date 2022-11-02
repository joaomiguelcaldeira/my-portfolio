DROP TABLE prescricao_venda CASCADE;
DROP TABLE venda_farmacia CASCADE;
DROP TABLE analise CASCADE;
DROP TABLE prescricao CASCADE;
DROP TABLE consulta CASCADE;
DROP TABLE instituicao CASCADE;
DROP TABLE medico CASCADE;
DROP TABLE concelho CASCADE;
DROP TABLE regiao CASCADE;

CREATE TABLE regiao (
        num_regiao integer,
        nome_regiao varchar(80) NOT NULL UNIQUE,
        num_habitantes integer NOT NULL,
        PRIMARY KEY(num_regiao),
        CHECK (nome_regiao IN ('Norte','Centro','Lisboa','Alentejo','Algarve')),
        CHECK (num_habitantes >= 0)
);

CREATE TABLE concelho (
        num_concelho integer,
        num_regiao integer,
        nome_concelho varchar(80) NOT NULL,
        num_habitantes_concelho integer NOT NULL,
        PRIMARY KEY(num_concelho,num_regiao),
        FOREIGN KEY(num_regiao) REFERENCES regiao(num_regiao) ON DELETE CASCADE,
        CHECK (nome_concelho IN ('Abrantes', 'Agueda', 'Aguiar da Beira', 'Alandroal', 'Albergaria-a-Velha', 'Albufeira', 'Alcacer do Sal', 'Alcanena', 'Alcobaca', 'Alcochete', 'Alcoutim', 'Alenquer', 'Alfandega da Fe', 'Alijo', 'Aljezur', 'Aljustrel', 'Almada', 'Almeida', 'Almeirim', 'Almodovar', 'Alpiarca', 'Alter do Chao', 'Alvaiazere', 'Alvito', 'Amadora', 'Amarante', 'Amares', 'Anadia', 'Ansiao', 'Arcos de Valdevez', 'Arganil', 'Armamar', 'Arouca', 'Arraiolos', 'Arronches', 'Arruda dos Vinhos', 'Aveiro', 'Avis', 'Azambuja', 'Baiao', 'Barcelos', 'Barrancos', 'Barreiro', 'Batalha', 'Beja', 'Belmonte', 'Benavente', 'Bombarral', 'Borba', 'Boticas', 'Braga', 'Braganca', 'Cabeceiras de Basto', 'Cadaval', 'Caldas da Rainha', 'Caminha', 'Campo Maior', 'Cantanhede', 'Carrazeda de Ansiaes', 'Carregal do Sal', 'Cartaxo', 'Cascais', 'Castanheira de Pera', 'Castelo Branco', 'Castelo de Paiva', 'Castelo de Vide', 'Castro Daire', 'Castro Marim', 'Castro Verde', 'Celorico da Beira', 'Celorico de Basto', 'Chamusca', 'Chaves', 'Cinfaes', 'Coimbra', 'Condeixa-a-Nova', 'Constancia', 'Coruche', 'Covilha', 'Crato', 'Cuba', 'Elvas', 'Entroncamento', 'Espinho', 'Esposende', 'Estarreja', 'Estremoz', 'Evora', 'Fafe', 'Faro', 'Felgueiras', 'Ferreira do Alentejo', 'Ferreira do Zezere', 'Figueira da Foz', 'Figueira de Castelo Rodrigo', 'Figueiro dos Vinhos', 'Fornos de Algodres', 'Freixo de Espada a Cinta', 'Fronteira', 'Fundao', 'Gaviao', 'Golega', 'Gondomar', 'Gouveia', 'Grandola', 'Guarda', 'Guimaraes', 'Gois', 'Idanha-a-Nova', 'Ilhavo', 'Lagoa', 'Lagos', 'Lamego', 'Leiria', 'Lisboa', 'Loule', 'Loures', 'Lourinha', 'Lousa', 'Lousada', 'Macao', 'Macedo de Cavaleiros', 'Mafra', 'Maia', 'Mangualde', 'Manteigas', 'Marco de Canaveses', 'Marinha Grande', 'Marvao', 'Matosinhos', 'Mealhada', 'Meda', 'Melgaco', 'Mesao Frio', 'Mira', 'Miranda do Corvo', 'Miranda do Douro', 'Mirandela', 'Mogadouro', 'Moimenta da Beira', 'Moita', 'Moncao', 'Monchique', 'Mondim de Basto', 'Monforte', 'Montalegre', 'Montemor-o-Novo', 'Montemor-o-Velho', 'Montijo', 'Mora', 'Mortagua', 'Moura', 'Mourao', 'Murca', 'Murtosa', 'Mertola', 'Nazare', 'Nelas', 'Nisa', 'Obidos', 'Odemira', 'Odivelas', 'Oeiras', 'Oleiros', 'Olhao', 'Oliveira de Azemeis', 'Oliveira de Frades', 'Oliveira do Bairro', 'Oliveira do Hospital', 'Ourique', 'Ourem', 'Ovar', 'Pacos de Ferreira', 'Palmela', 'Pampilhosa da Serra', 'Paredes', 'Paredes de Coura', 'Pedrogao Grande', 'Penacova', 'Penafiel', 'Penalva do Castelo', 'Penamacor', 'Penedono', 'Penela', 'Peniche', 'Peso da Regua', 'Pinhel', 'Pombal', 'Ponte da Barca', 'Ponte de Lima', 'Ponte de Sor', 'Portalegre', 'Portel', 'Portimao', 'Porto', 'Porto de Mos', 'Proenca-a-Nova', 'Povoa de Lanhoso', 'Povoa de Varzim', 'Redondo', 'Reguengos de Monsaraz', 'Resende', 'Ribeira de Pena', 'Rio Maior', 'Sabrosa', 'Sabugal', 'Salvaterra de Magos', 'Santa Comba Dao', 'Santa Maria da Feira', 'Santa Marta de Penaguiao', 'Santarem', 'Santiago do Cacem', 'Santo Tirso', 'Sao Bras de Alportel', 'Sao Joao da Madeira', 'Sao Joao da Pesqueira', 'Sao Pedro do Sul', 'Sardoal', 'Satao', 'Seia', 'Seixal', 'Sernancelhe', 'Serpa', 'Serta', 'Sesimbra', 'Setubal', 'Sever do Vouga', 'Silves', 'Sines', 'Sintra', 'Sobral de Monte Agraco', 'Soure', 'Sousel', 'Tabua', 'Tabuaco', 'Tarouca', 'Tavira', 'Terras de Bouro', 'Tomar', 'Tondela', 'Torre de Moncorvo', 'Torres Novas', 'Torres Vedras', 'Trancoso', 'Trofa', 'Vagos', 'Vale de Cambra', 'Valenca', 'Valongo', 'Valpacos', 'Vendas Novas', 'Viana do Alentejo', 'Viana do Castelo', 'Vidigueira', 'Vieira do Minho', 'Vila Flor', 'Vila Franca de Xira', 'Vila Nova da Barquinha', 'Vila Nova de Cerveira', 'Vila Nova de Famalicao', 'Vila Nova de Foz Côa', 'Vila Nova de Gaia', 'Vila Nova de Paiva', 'Vila Nova de Poiares', 'Vila Pouca de Aguiar', 'Vila Real', 'Vila Real de Santo Antonio', 'Vila Velha de Rodao', 'Vila Verde', 'Vila Vicosa', 'Vila de Rei', 'Vila do Bispo', 'Vila do Conde', 'Vimioso', 'Vinhais', 'Viseu', 'Vizela', 'Vouzela'))
);

CREATE TABLE instituicao (
        nome varchar(80),
        tipo varchar(80) NOT NULL,
        num_regiao integer,
        num_concelho integer,
        PRIMARY KEY (nome),
        CHECK (tipo IN ('farmacia','laboratorio','clinica','hospital')),
        FOREIGN KEY (num_concelho,num_regiao) REFERENCES concelho(num_concelho,num_regiao) ON DELETE CASCADE
);

CREATE TABLE medico (
        num_cedula integer,
        nome varchar(80) NOT NULL,
        especialidade varchar(80) NOT NULL,
        CHECK (num_cedula >= 0),
        PRIMARY KEY (num_cedula)
);


CREATE TABLE consulta (
        num_cedula integer,
        num_doente integer,
        data date,
        nome_instituicao varchar(80),
        PRIMARY KEY (num_cedula,num_doente,data),
        CHECK (EXTRACT(DOW FROM data) != 0 AND EXTRACT(DOW FROM data) != 6),
        UNIQUE (num_doente,data,nome_instituicao),      
        FOREIGN KEY (num_cedula) REFERENCES medico(num_cedula) ON DELETE CASCADE, 
        FOREIGN KEY(nome_instituicao) REFERENCES instituicao(nome) ON DELETE CASCADE
);

CREATE TABLE prescricao (
        num_cedula integer,
        num_doente integer,
        data date,
        substancia varchar(80),
        quant numeric(8,2) NOT NULL,
        PRIMARY KEY (num_cedula,num_doente,data,substancia),
        FOREIGN KEY (num_cedula,num_doente,data) REFERENCES consulta(num_cedula,num_doente,data) ON DELETE CASCADE ON UPDATE CASCADE,
        CHECK (quant > 0)
); 

CREATE TABLE analise (  
        num_analise integer,
        especialidade varchar(80) NOT NULL,
        num_cedula integer,
        num_doente integer,
        data date,
        data_registo date NOT NULL,
        nome varchar(80) NOT NULL,
        quant numeric(8,2),
        inst varchar(80) NOT NULL,
        PRIMARY KEY (num_analise),
        FOREIGN KEY (num_cedula,num_doente,data) REFERENCES consulta(num_cedula,num_doente,data) ON DELETE SET NULL ON UPDATE CASCADE,
        FOREIGN KEY (inst) REFERENCES instituicao(nome) ON DELETE CASCADE
);

CREATE TABLE venda_farmacia (
        num_venda integer,
        data_registo date NOT NULL,
        substancia varchar(80) NOT NULL,
        quant numeric(8,2) NOT NULL,
        preco numeric(8,2) NOT NULL,
        inst varchar(80) NOT NULL,
        PRIMARY KEY (num_venda),
        FOREIGN KEY (inst) REFERENCES instituicao(nome) ON DELETE CASCADE
);

CREATE TABLE prescricao_venda (
        num_cedula integer,
        num_doente integer,
        data date,
        substancia varchar(80),
        num_venda integer UNIQUE,
        PRIMARY KEY (num_cedula,num_doente,data,substancia,num_venda),
        FOREIGN KEY (num_cedula,num_doente,substancia,data) REFERENCES prescricao(num_cedula,num_doente,substancia,data) ON DELETE CASCADE ON UPDATE CASCADE,
        FOREIGN KEY (num_venda) REFERENCES venda_farmacia(num_venda) ON DELETE CASCADE
);


\i RI.sql;
\i populate.sql;