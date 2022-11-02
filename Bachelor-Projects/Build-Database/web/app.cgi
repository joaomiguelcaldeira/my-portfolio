#!/usr/bin/python3

from wsgiref.handlers import CGIHandler
from flask import Flask
from flask import render_template, request

## Libs postgres
import psycopg2
import psycopg2.extras

app = Flask(__name__)

## SGBD configs
DB_HOST= #EDIT YOUR HOST
DB_USER= #EDIT DB USER 
DB_DATABASE=DB_USER
DB_PASSWORD= #EDIT DB PASS 
DB_CONNECTION_STRING = "host=%s dbname=%s user=%s password=%s" % (DB_HOST, DB_DATABASE, DB_USER, DB_PASSWORD)

## Runs the function once the root page is requested.
## The request comes with the folder structure setting ~/web as the root
@app.route('/')
def load_menu():
	try:
			return render_template("menu.html")
	except Exception as e:
			return str(e)

@app.route('/voltar')
def reload_menu():
	try:
			return render_template("menu.html")
	except Exception as e:
			return str(e)

@app.route('/medicos')
def load_medicos():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = "SELECT * FROM medico;"
		cursor.execute(query)
		return render_template("medicos.html", cursor=cursor)
	except Exception as e:
			return str(e) #Renders a page with the error.
	finally:
		cursor.close()
		dbConn.close()


@app.route('/novo_medico_menu')
def novo_medico_menu():
	try:
		return render_template("novo_medico_menu.html")
	except Exception as e:
		return str(e)

@app.route('/novo_medico', methods=["POST"])
def novo_medico():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''INSERT INTO medico(num_cedula, nome, especialidade) VALUES(%s, %s, %s);'''
		cursor.execute(query,(request.form["num_cedula"], request.form["nome"],request.form["especialidade"]),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_medicos()


@app.route('/edita_medico_menu')
def edita_medico_menu():
	try:
		return render_template("edita_medico_menu.html",params=request.args)
	except Exception as e:
		return str(e)


@app.route('/editar_medico', methods=["POST"])
def editar_medico():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''UPDATE medico SET nome= %s, especialidade = %s WHERE num_cedula = %s;'''
		cursor.execute(query, (request.form["nome"],request.form["especialidade"],request.form["num_cedula"]),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_medicos()

@app.route('/apagar_medico')
def apagar_medico():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''DELETE FROM medico WHERE num_cedula = %s;'''
		cursor.execute(query, (request.args["num_cedula"], ))
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_medicos()

@app.route('/instituicoes')
def load_instituicoes():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = "SELECT * FROM instituicao;"
		cursor.execute(query)
		return render_template("instituicoes.html", cursor=cursor)
	except Exception as e:
			return str(e) #Renders a page with the error.
	finally:
		cursor.close()
		dbConn.close()

@app.route('/nova_instituicao_menu')
def nova_instituicao_menu():
	try:
		return render_template("nova_instituicao_menu.html")
	except Exception as e:
		return str(e)

@app.route('/nova_instituicao', methods=["POST"])
def nova_instituicao():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''INSERT INTO instituicao(nome, tipo, num_regiao, num_concelho) VALUES(%s, %s, %s, %s );'''
		cursor.execute(query,(request.form["nome"],request.form["tipo"],request.form["num_regiao"],request.form["num_concelho"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_instituicoes()

@app.route('/edit_instituicao', methods=["POST"])
def edit_instituicao():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''UPDATE instituicao SET tipo=%s, num_regiao = %s, num_concelho = %s WHERE nome = %s;'''
		cursor.execute(query,(request.form["tipo"],request.form["num_regiao"],request.form["num_concelho"],request.form["nome"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_instituicoes()

@app.route('/delete_instituicao')
def delete_instituicao():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''DELETE FROM instituicao WHERE nome = %s;'''
		cursor.execute(query,(request.args["nome"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_instituicoes()

@app.route('/edita_instituicao_menu')
def edita_instituicao_menu():
	try:
		return render_template("edita_instituicao_menu.html",params=request.args)
	except Exception as e:
		return str(e)

@app.route('/prescricoes')
def load_prescricoes():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = "SELECT * FROM prescricao;"
		cursor.execute(query)
		return render_template("prescricoes.html", cursor=cursor)
	except Exception as e:
			return str(e) #Renders a page with the error.
	finally:
		cursor.close()
		dbConn.close()

@app.route('/nova_prescricao_menu')
def nova_prescricao_menu():
	try:
		return render_template("nova_prescricao_menu.html")
	except Exception as e:
		return str(e)

@app.route('/nova_prescricao', methods=["POST"])
def nova_prescricao():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''INSERT INTO prescricao(num_cedula, num_doente, data, substancia, quant) VALUES(%s, %s, %s, %s, %s );'''
		cursor.execute(query,(request.form["num_cedula"],request.form["num_doente"],request.form["data"],request.form["substancia"],request.form["quant"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_prescricoes()

@app.route('/delete_prescricao')
def delete_prescricao():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''DELETE FROM prescricao WHERE num_cedula = %s  AND num_doente = %s AND data = %s AND substancia = %s;'''
		cursor.execute(query,(request.args["num_cedula"],request.args["num_doente"],request.args["data"],request.args["substancia"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_prescricoes()

@app.route('/edita_prescricao_menu')
def edita_prescricao_menu():
	try:
		return render_template("edita_prescricao_menu.html",params=request.args)
	except Exception as e:
		return str(e)

@app.route('/editar_prescricao', methods=["POST"])
def edit_prescricao():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''UPDATE prescricao SET quant = %s, substancia = %s WHERE num_cedula = %s AND num_doente = %s AND data = %s AND substancia = %s;'''
		cursor.execute(query,(request.form["quant"],request.form["new_substancia"],request.form["num_cedula"],request.form["num_doente"],request.form["data"],request.form["substancia"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_prescricoes()

@app.route('/analises')
def load_analises():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = "SELECT * FROM analise;"
		cursor.execute(query)
		return render_template("analises.html", cursor=cursor)
	except Exception as e:
			return str(e) #Renders a page with the error.
	finally:
		cursor.close()
		dbConn.close()

@app.route('/edita_analise_menu')
def edita_analise_menu():
	try:
		return render_template("edita_analise_menu.html",params=request.args)
	except Exception as e:
		return str(e)

@app.route('/nova_analise_menu')
def nova_analise_menu():
	try:
		return render_template("nova_analise_menu.html")
	except Exception as e:
		return str(e)

@app.route('/edita_analise', methods=["POST"])
def edita_analise():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''UPDATE analise SET data_registo = %s, nome = %s, quant = %s, inst = %s WHERE num_analise = %s;'''
		cursor.execute(query,(request.form["data_registo"],request.form["nome"],request.form["quant"],request.form["inst"],request.form["num_analise"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_analises()

@app.route('/nova_analise', methods=["POST"])
def nova_analise():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''INSERT INTO analise(num_analise, especialidade, num_cedula, num_doente, data, data_registo, nome, quant,inst) VALUES(%s, %s, %s, %s, %s, %s, %s, %s, %s);'''
		cursor.execute(query,(request.form["num_analise"],request.form["especialidade"],request.form["num_cedula"],request.form["num_doente"],request.form["data"],request.form["data_registo"],request.form["nome"],request.form["quant"],request.form["inst"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_analises()

@app.route('/delete_analise')
def delete_analise():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''DELETE FROM analise WHERE num_analise = %s;'''
		cursor.execute(query,(request.args["num_analise"]),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_analises()

@app.route('/listar_valores_glicemia')
def listar_valores_glicemia():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''SELECT * FROM (SELECT num_doente, foo.num_concelho, foo.max FROM instituicao as i, analise as a,(SELECT num_concelho, MAX(quant) from analise as a, instituicao as i 
		WHERE i.nome = a.inst AND a.nome = 'analise_de_glicemia'group by num_concelho) as foo WHERE a.quant = foo.max and i.nome = a.inst
		and i.num_concelho = foo.num_concelho) as maxT inner join
		(SELECT num_doente, foo.num_concelho, foo.min FROM instituicao as i, analise as a,(SELECT num_concelho, MIN(quant) from analise as a, instituicao as i 
		WHERE i.nome = a.inst AND a.nome = 'analise_de_glicemia'group by num_concelho) as foo WHERE a.quant = foo.min and i.nome = a.inst
		and i.num_concelho = foo.num_concelho) as minT on (minT.num_concelho = maxT.num_concelho);'''
		cursor.execute(query)
		return render_template("valores_glicemia.html", cursor=cursor)
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()

@app.route('/listar_subs_prescritas')
def load_subs_presc():
		try:
				return render_template("get_subs_presc.html")
		except Exception as e:
				return str(e) #Renders a page with the error.

@app.route('/listar_subs', methods=["POST"])
def listar():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''SELECT substancia FROM prescricao AS p WHERE num_cedula = %s AND EXTRACT(MONTH FROM p.data) = %s AND EXTRACT(YEAR FROM p.data) = %s;'''
		cursor.execute(query,(request.form["num_cedula"],request.form["month"],request.form["year"],),)
		return render_template("lista_subs.html", cursor=cursor)
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()


@app.route('/realizar_venda')
def load_vendas():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = "SELECT * FROM venda_farmacia;"
		cursor.execute(query)
		return render_template("vendas.html", cursor=cursor)
	except Exception as e:
			return str(e) #Renders a page with the error.
	finally:
		cursor.close()
		dbConn.close()


@app.route('/venda_prescricao_menu')
def venda_prescricao_menu():
	try:
		return render_template("venda_prescricao_menu.html",params=request.args)
	except Exception as e:
		return str(e)

@app.route('/venda_farmacia')
def venda_farmacia():
	try:
		return render_template("venda_farmacia_menu.html")
	except Exception as e:
		return str(e)

@app.route('/venda_sem_prescricao', methods=["POST"])
def venda_sem_prescricao():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''INSERT INTO venda_farmacia(num_venda , data_registo, substancia, quant, preco, inst) VALUES(%s, %s, %s, %s, %s, %s);'''
		cursor.execute(query,(request.form["num_venda"],request.form["data_registo"],request.form["substancia"],request.form["quant"],request.form["preco"],request.form["inst"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_vendas()

@app.route('/venda_com_prescricao', methods=["POST"])
def venda_com_prescricao():
	dbConn=None
	cursor=None
	try:
		dbConn = psycopg2.connect(DB_CONNECTION_STRING)
		cursor = dbConn.cursor(cursor_factory = psycopg2.extras.DictCursor)
		query = f'''INSERT INTO venda_farmacia(num_venda, data_registo, substancia, quant, preco, inst) VALUES(%s, %s, %s, %s, %s,%s);'''
		cursor.execute(query,(request.form["num_venda"],request.form["data_registo"],request.form["substancia"],request.form["quant"],request.form["preco"],request.form["inst"],),)
		query = f'''INSERT INTO prescricao_venda(num_cedula, num_doente, data, substancia, num_venda) VALUES(%s, %s, %s, %s, %s);'''
		cursor.execute(query,(request.form["num_cedula"],request.form["num_doente"],request.form["data"],request.form["substancia"],request.form["num_venda"],),)
		return query
	except Exception as e:
		return str(e) 
	finally:
		dbConn.commit()
		cursor.close()
		dbConn.close()
		return load_vendas()

CGIHandler().run(app)