# Sistema de Entregas — Tabela Hash

## Integrantes do Grupo
- Luccas Henrique Vieira — 2023010182
- Matheus Garcia Sampaio — 2023010191
- Ranier Sales Veras — 2023011223

## Descrição
O sistema foi desenvolvido em C e Python, com uma interface web simples. Ele permite cadastrar, buscar e gerenciar pedidos de entrega, simulando o funcionamento de uma empresa do ramo logístico.

A estrutura principal de dados utilizada é a tabela hash, que garante rapidez nas operações de inserção e busca dos pedidos.

## Funcionalidades
- Cadastro de novos pedidos
- Busca de pedidos por identificador
- Listagem de pedidos
- Interface web para interação

## Estrutura do Projeto
- `main.c`: Código principal em C, responsável pela lógica da tabela hash e operações com pedidos.
- `hash.c` e `hash.h`: Implementação da tabela hash e funções auxiliares.
- `app.py`: Aplicação web (provavelmente usando Flask), que serve as páginas HTML e interage com o sistema em C.
- `templates/`: Páginas HTML da interface (admin, usuário, base, index).
- `static/`: Arquivos estáticos (CSS, imagens).
- `output/`: Possível local de binários gerados.

## Como Executar
1. Compile o código C:
   ```powershell
   gcc main.c hash.c -o output/main.exe
   ```
2. Execute a aplicação web Python:
   ```powershell
   python app.py
   ```
3. Acesse a interface pelo navegador, geralmente em `http://localhost:5000`.

## Requisitos
- Python 3.x
- Flask (`pip install flask`)
- Compilador C (gcc)

## Observações
- O sistema é um protótipo acadêmico, focado em demonstrar o uso de tabelas hash em aplicações reais.
- Sinta-se livre para modificar e expandir as funcionalidades!

---

Desenvolvido para fins educacionais.
