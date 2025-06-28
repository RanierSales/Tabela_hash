from flask import Flask, render_template, request, redirect, url_for
import subprocess

app = Flask(__name__)

# função para executar o programa C
def executar_comando(args):
    try:
        resultado = subprocess.check_output(["./pedidos"] + args).decode()
    except subprocess.CalledProcessError as e:
        resultado = e.output.decode()
    return resultado

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/usuario", methods=["GET", "POST"])
def usuario():
    resultado = ""
    if request.method == "POST":
        codigo = request.form["codigo"]
        resultado = executar_comando(["buscar", codigo])
    return render_template("usuario.html", resultado=resultado)

@app.route("/admin", methods=["GET", "POST"])
def admin():
    resultado = ""
    if request.method == "POST":
        acao = request.form["acao"]
        codigo = request.form.get("codigo", "")
        status = request.form.get("status", "")

        if acao == "buscar":
            resultado = executar_comando(["buscar", codigo])
        elif acao == "inserir":
            resultado = executar_comando(["inserir", codigo, status])
        elif acao == "remover":
            resultado = executar_comando(["remover", codigo])
        elif acao == "listar":
            resultado = executar_comando(["listar"])
    return render_template("admin.html", resultado=resultado)

if __name__ == "__main__":
    app.run(debug=True)
