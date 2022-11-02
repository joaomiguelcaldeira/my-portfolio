--Instituicoes--
INSERT INTO instituicao(nome, tipo, num_regiao, num_concelho) VALUES('farmacia_de_odivelas','farmacia',2,10);

--Consultas--
INSERT INTO consulta(num_cedula, num_doente, data, nome_instituicao) VALUES(9,9,'02/01/2017','Hospital_Central_de_Arouca');
INSERT INTO consulta(num_cedula, num_doente, data, nome_instituicao) VALUES(11,11,'02/02/2017','Hospital_do_Porto');
INSERT INTO consulta(num_cedula, num_doente, data, nome_instituicao) VALUES(12,12,'03/04/2017','Hospital_Central_de_Arouca');
INSERT INTO consulta(num_cedula, num_doente, data, nome_instituicao) VALUES(1,1,'02/06/2017','Hospital_do_Porto');
INSERT INTO consulta(num_cedula, num_doente, data, nome_instituicao) VALUES(3,3,'02/08/2017','Hospital_de_vila_franca');
INSERT INTO consulta(num_cedula, num_doente, data, nome_instituicao) VALUES(2,2,'01/01/2020','Hospital_de_vila_franca');
INSERT INTO consulta(num_cedula, num_doente, data, nome_instituicao) VALUES(5,5,'03/02/2020','Hospital_de_vila_franca');

--prescricoes--
INSERT INTO prescricao(num_cedula, num_doente, data, substancia, quant) VALUES(9,9,'02/01/2017','acucar',2);
INSERT INTO prescricao(num_cedula, num_doente, data, substancia, quant) VALUES(11,11,'02/02/2017','acucar',1);
INSERT INTO prescricao(num_cedula, num_doente, data, substancia, quant) VALUES(12,12,'03/04/2017','acucar',2);
INSERT INTO prescricao(num_cedula, num_doente, data, substancia, quant) VALUES(12,12,'02/06/2017','acucar',1);
INSERT INTO prescricao(num_cedula, num_doente, data, substancia, quant) VALUES(2,2,'01/01/2020','glicerina',1);
INSERT INTO prescricao(num_cedula,num_doente,data, substancia, quant) VALUES(5,5,'03/02/2020','cha_verde',1);

--Analises--
INSERT INTO analise(num_analise, especialidade, num_cedula, num_doente, data, data_registo, nome, quant, inst) VALUES(6,'radiologia',9,9,'02/01/2017','02/01/2017','analise_de_glicemia',1,'Hospital_Central_de_Arouca');
INSERT INTO analise(num_analise, especialidade, num_cedula, num_doente, data, data_registo, nome, quant, inst) VALUES(7,'cardiologia',11,11,'02/02/2017','02/02/2017','analise_de_glicemia',1,'Hospital_do_Porto');
INSERT INTO analise(num_analise, especialidade, num_cedula, num_doente, data, data_registo, nome, quant, inst) VALUES(8,'ortopedia',12,12,'03/04/2017','03/04/2017','analise_de_glicemia',1,'Hospital_Central_de_Arouca');
INSERT INTO analise(num_analise, especialidade, num_cedula, num_doente, data, data_registo, nome, quant, inst) VALUES(9,'cardiologia',1,1,'02/06/2017','02/06/2017','analise_de_glicemia',1,'Hospital_do_Porto');
INSERT INTO analise(num_analise, especialidade, num_cedula, num_doente, data, data_registo, nome, quant, inst) VALUES(10,'anestesiologia',3,3,'02/08/2017','02/08/2017','analise_de_glicemia',1,'Hospital_de_vila_franca');


--Vendas_Farmacia--
INSERT INTO venda_farmacia(num_venda, data_registo, substancia, quant, preco, inst) VALUES(31,'16/01/2017','acucar',10.0,5.75,'farmacia_central');
INSERT INTO venda_farmacia(num_venda, data_registo, substancia, quant, preco, inst) VALUES(32,'01/01/2020','glicerina',1,2.75,'farmacia_central_de_sintra');
INSERT INTO venda_farmacia(num_venda, data_registo, substancia, quant, preco, inst) VALUES(33,'01/01/2020','glicerina',1,2.75,'farmacia_central_de_sintra');
INSERT INTO venda_farmacia(num_venda, data_registo, substancia, quant, preco, inst) VALUES(34,'03/02/2020','cha_verde',1,1.65,'farmacia_de_odivelas');

--prescricao_venda--
INSERT INTO prescricao_venda(num_cedula, num_doente, data, substancia, num_venda) VALUES(2,2,'01/01/2020','glicerina',32);
INSERT INTO prescricao_venda(num_cedula, num_doente, data, substancia, num_venda) VALUES(5,5,'03/02/2020','cha_verde',33);


--d_tempo--
INSERT INTO d_tempo(dia,dia_da_semana, semana, mes, trimestre, ano) (SELECT DISTINCT EXTRACT(day FROM data_registo) AS dia,EXTRACT(dow FROM data_registo) AS dia_da_semana,EXTRACT(week FROM data_registo) AS dia_da_semana,
EXTRACT(month FROM data_registo) AS mes,EXTRACT(quarter FROM data_registo) AS trimestre,EXTRACT(year FROM data_registo) AS ano FROM analise);

INSERT INTO d_tempo(dia,dia_da_semana, semana, mes, trimestre, ano) (SELECT DISTINCT EXTRACT(day FROM data_registo) AS dia,EXTRACT(dow FROM data_registo) AS dia_da_semana,EXTRACT(week FROM data_registo) AS dia_da_semana,
EXTRACT(month FROM data_registo) AS mes,EXTRACT(quarter FROM data_registo) AS trimestre,EXTRACT(year FROM data_registo) AS ano FROM venda_farmacia 
WHERE ((SELECT EXTRACT(day FROM data_registo)),(SELECT EXTRACT(month FROM data_registo)),(SELECT EXTRACT(year FROM data_registo))) NOT IN (SELECT dia,mes,ano FROM d_tempo));

INSERT INTO d_tempo(dia,dia_da_semana, semana, mes, trimestre, ano) (SELECT DISTINCT EXTRACT(day FROM data) AS dia,EXTRACT(dow FROM data) AS dia_da_semana,EXTRACT(week FROM data) AS dia_da_semana,
EXTRACT(month FROM data) AS mes,EXTRACT(quarter FROM data) AS trimestre,EXTRACT(year FROM data) AS ano FROM prescricao_venda 
WHERE ((SELECT EXTRACT(day FROM data)),(SELECT EXTRACT(month FROM data)),(SELECT EXTRACT(year FROM data))) NOT IN (SELECT dia,mes,ano FROM d_tempo));


--d_instituicao--

INSERT INTO d_instituicao(nome,tipo,num_regiao,num_concelho) (SELECT * FROM instituicao);


--f_analise--


INSERT INTO f_analise(select a.num_analise, a.num_cedula, a.num_doente , t.id_tempo, i.id_inst, a.nome, a.quant FROM d_instituicao AS i, analise AS a, d_tempo AS t,instituicao AS ins 
WHERE a.inst = ins.nome AND a.inst = i.nome AND t.dia = EXTRACT(DAY FROM a.data_registo) AND t.mes = EXTRACT(MONTH FROM a.data_registo) AND t.ano = EXTRACT(YEAR FROM a.data_registo));

--f_presc_venda--


INSERT INTO f_presc_venda(SELECT DISTINCT p.num_venda,m.num_cedula,p.num_doente ,t.id_tempo,i.id_inst,p.substancia,q.quant FROM  d_instituicao AS i ,consulta AS c 
NATURAL JOIN medico AS m NATURAL JOIN prescricao_venda AS p NATURAL JOIN prescricao AS q ,d_tempo AS t WHERE t.dia = EXTRACT(DAY FROM p.data) 
AND t.semana = EXTRACT(WEEK FROM p.data) AND t.mes = EXTRACT(MONTH FROM p.data) AND t.ano = EXTRACT(year FROM p.data) AND i.nome = c.nome_instituicao);

