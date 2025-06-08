# Gerar um relatório em formato Excel (.xlsx) com os dados atualizados

import pandas as pd

# Coloquei o caminho completo do arquivo, pois o mesmo não estava sendo encontrado somente pelo nome
df = pd.read_csv("C:/Users/julya/OneDrive/Desktop/P.I/Márcia - LOP/LOPAL-ProjetoIntegrador.csv")

# Salvar como arquivo Excel
df.to_excel("C:/Users/julya/OneDrive/Desktop/P.I/Márcia - LOP/LOPAL-ProjetoIntegrador.xlsx", index=False)



