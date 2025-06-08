"""
Gerar uma página HTML com todas as linhas do arquivo, interpretando os valores de cada esteira com seus significados e cores/emojis. A página deve conter o título:
"Status das Esteiras - Monitoramento de Estoque".
"""

import pandas as pd 

df = pd.read_csv("LOPAL-ProjetoIntegrador.csv") # Lê o arquivo csv e armazena em um DataFrame

# Armazenamento do código HTML na variável tabela 
tabela_html = df.to_html(index=False) # to_html -> Converte a tabela em código HTML / index=False -> ignora a coluna do índice no HTML (csv cria uma coluna índice a esquerda)
    
# Montar o código em HTML dentro do with open
with open ("LOPAL_PI.html", 'w') as lopal_html:     # With -> existe para não ser necessário fechar o arquivo depois e garante que o arquivo seja fechado corretamente / 'W' -> Modo write
    lopal_html.write("<!DOCTYPE html>\n")   # Documento HTML 5
    lopal_html.write("<html>\n")    # Início página HTML
    lopal_html.write("<head>\n")
    lopal_html.write("<title>Status das Esterias - Monitoramento de Estoque</title>\n")   
    lopal_html.write("</head>\n")
    lopal_html.write("<body>\n")
    lopal_html.write(tabela_html)
    lopal_html.write("</body>\n")
    lopal_html.write("</html>\n")   # Fim página HTML 