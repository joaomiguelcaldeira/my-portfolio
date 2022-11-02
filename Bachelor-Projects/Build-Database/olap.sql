--QUERIES DATA ANALYTICS--

--QUERIE 1--
SELECT DISTINCT count(id_analise) AS numero_de_analises_de_glicemia ,m.especialidade,t.mes,t.ano 
FROM f_analise AS a,medico AS m,d_tempo as t WHERE a.nome = 'analise_de_glicemia' 
AND m.num_cedula = a.id_medico AND a.id_data_registo = t.id_tempo AND t.ano <= 2020 AND t.ano >=2017 GROUP BY CUBE(m.especialidade,t.mes,t.ano);

--QUERIE 2--
SELECT sum(quant) AS quantidade_total, count(id_presc_venda) AS n_medio_de_prescricoes_diario,substancia,num_concelho 
FROM f_presc_venda AS p,d_tempo AS t,d_instituicao AS i WHERE t.ano =2020 AND p.id_data_registo = t.id_tempo 
AND t.trimestre = 1 AND p.id_inst = i.id_inst AND i.num_regiao = 2 GROUP BY ROLLUP(i.num_concelho,(t.dia_da_semana,t.mes), p.substancia);