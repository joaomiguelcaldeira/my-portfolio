--RI analise--
DROP TRIGGER IF EXISTS same_especialidades_trigger ON analise;

create or replace function same_especialidades() returns trigger AS $$
begin
        if (new.num_cedula IS NULL and
        new.num_doente IS NULL and
        new.data IS NULL)
        then return new;
        end if;
        if (new.especialidade NOT IN (SELECT especialidade FROM medico
		WHERE num_cedula = new.num_cedula))
        then raise exception'Especialidade do medico nao corresponde a especialidade da consulta na analise %',new.num_analise;
        end if;
        return new;
End;

$$ Language plpgsql;

create trigger same_especialidades_trigger before insert OR UPDATE ON analise for each row execute procedure same_especialidades();

--RI 100--

DROP TRIGGER IF EXISTS medico_consultas_trigger ON consulta;

create or replace function medico_consultas() returns trigger AS $$
begin
        if new.num_cedula IN (SELECT num_cedula FROM(SELECT num_cedula, count(num_cedula) 
                       FROM consulta as c WHERE EXTRACT(WEEK FROM c.data) = EXTRACT(WEEK FROM new.data) 
                       AND EXTRACT(YEAR FROM c.data) = EXTRACT(YEAR FROM new.data) 
                       AND c.nome_instituicao = new.nome_instituicao GROUP BY c.num_cedula HAVING count(num_cedula) >= 100) AS foo 
                       GROUP BY num_cedula)
        then

        raise exception'Medico % ja tem 100 consultas nessa instituicao e nessa semana',new.num_cedula;
        end if;
return new;
End;
$$ Language plpgsql;

create trigger medico_consultas_trigger before insert on consulta for each row execute procedure medico_consultas();