
DROP TABLE f_analise CASCADE;
DROP TABLE f_presc_venda CASCADE;
DROP TABLE d_instituicao CASCADE;
DROP TABLE d_tempo CASCADE;


CREATE TABLE d_tempo (
        id_tempo serial,
        dia integer NOT NULL,
        dia_da_semana integer NOT NULL,
        semana integer NOT NULL,
        mes integer NOT NULL,
        trimestre integer NOT NULL,
        ano integer NOT NULL,
        PRIMARY KEY(id_tempo)
);


CREATE TABLE d_instituicao (
        id_inst serial,
        nome varchar(80) NOT NULL,
        tipo varchar(80) NOT NULL,
        num_regiao integer,
        num_concelho integer,
        PRIMARY KEY(id_inst),
        FOREIGN KEY (nome) REFERENCES instituicao(nome) ON DELETE CASCADE ,
        FOREIGN KEY (num_concelho,num_regiao) REFERENCES concelho(num_concelho,num_regiao) ON DELETE CASCADE
);


CREATE TABLE f_presc_venda (
        id_presc_venda integer,
        id_medico integer,
        num_doente integer NOT NULL,
        id_data_registo integer NOT NULL,
        id_inst integer,
        substancia varchar(80) NOT NULL,
        quant integer NOT NULL,
        PRIMARY KEY(id_presc_venda),
        FOREIGN KEY(id_presc_venda) REFERENCES prescricao_venda(num_venda) ON DELETE CASCADE,
        FOREIGN KEY(id_medico) REFERENCES medico(num_cedula) ON DELETE CASCADE,
        FOREIGN KEY(id_data_registo) REFERENCES d_tempo(id_tempo) ON DELETE CASCADE ,
        FOREIGN KEY(id_inst) REFERENCES d_instituicao(id_inst) ON DELETE CASCADE
);


CREATE TABLE f_analise (
        id_analise integer,
        id_medico integer,
        num_doente integer,
        id_data_registo integer,
        id_inst integer,
        nome varchar(80) NOT NULL,
        quant integer NOT NULL,
        PRIMARY KEY(id_analise),
        FOREIGN KEY (id_analise) REFERENCES analise(num_analise) ON DELETE CASCADE,
        FOREIGN KEY (id_medico) REFERENCES medico(num_cedula) ON DELETE CASCADE,
        FOREIGN KEY (id_data_registo) REFERENCES d_tempo(id_tempo) ON DELETE CASCADE,
        FOREIGN KEY (id_inst) REFERENCES d_instituicao(id_inst) ON DELETE CASCADE
);