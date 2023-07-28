import numpy as np
import matplotlib.pyplot as plt

import sys
nomedosarquivos = sys.argv



#Importando Dados 1

arquivo = open(nomedosarquivos[1], 'r') 
linhas = arquivo.readlines()
arquivo.close()

listaUfs = []
listaQuantidades = []
for line in linhas: #Somatiza os valores por regiao e separa as informacoes do arquivo em 2 listas

    siglaUf = line.split(' ')[0] #separa por ' ' [0] = primeira palavra
    quantidadeUf = line.split(' ')[1]
    listaUfs.append(siglaUf) #adiciona siglauf na lista de ufs
    listaQuantidades.append(int(quantidadeUf)/1000) #dividiu em milhoes de reais
    


#Grafico de Barras - Local e Quantidade Total

fig = plt.figure(figsize=(10,6)) #criando uma imagem deste tamanho
barra = fig.add_subplot(111) #adicionando um grafico DE BARRAS

ind = np.arange(len(listaUfs)) #Espacamento entre barras de estados len = qtas ufs tem
width = 0.4 #Largura da barra

t = int(max(listaQuantidades))
t = int(t/1000)
t = t + 1
t = t * 1000 #Limite superior do valor (teto em escala de milhares) ta arredondando pra saber o teto

barra.set_xlim(-2*width,len(ind)) #limites laterais
barra.set_ylim(0, t) #limites inferior e superior
barra.set_ylabel('Quantidade em milhões') #texto lateral
plt.title('Total de Peixes por Estado', y=1.075, x=0.815, bbox={'facecolor':'0.8', 'pad':5}) #texto superior
barra.set_xticks(ind) #espacamento entre barras ind la em cima
xtickNames = barra.set_xticklabels(listaUfs) #unidades inferiores (estados)
plt.setp(xtickNames, rotation=90, fontsize=10) #insercao dos textos inferiores em vertical
rects1 = barra.bar(ind, listaQuantidades, width, color="navy") #insercao das barras
barra.set_position([0.1, 0.1, 0.85, 0.75]) #[left, bottom, width, height] tamanho e posicao do grafico
plt.savefig(('Bar-' + nomedosarquivos[1]).replace('txt', 'png'), dpi=300) #salva grafico em imagem png

'''------------------------------------------------------------------------------------------------------------------'''



#Importando Dados 2

arquivo = open(nomedosarquivos[2], 'r') 
linhas = arquivo.readlines()
arquivo.close()

listaUfs = []
listaValores = []
for line in linhas: #Somatiza os valores por regiao e separa as informacoes do arquivo em 2 listas

    siglaUf = line.split(' ')[0] #separa por ' ' [0] = primeira palavra
    valorUf = line.split(' ')[1]
    listaUfs.append(siglaUf) #adiciona siglauf na lista de ufs
    listaValores.append(int(valorUf)/1000) #dividiu em milhoes de reais
    


#Grafico de Barras - Local e Valor Total

fig = plt.figure(figsize=(10,6)) #criando uma imagem deste tamanho
barra = fig.add_subplot(111) #adicionando um grafico DE BARRAS

ind = np.arange(len(listaUfs)) #Espacamento entre barras de estados len = qtas ufs tem
width = 0.4 #Largura da barra

t = int(max(listaValores))
t = int(t/1000)
t = t + 1
t = t * 1000 #Limite superior do valor (teto em escala de milhares) ta arredondando pra saber o teto

barra.set_xlim(-2*width,len(ind)) #limites laterais
barra.set_ylim(0, t) #limites inferior e superior
barra.set_ylabel('Valor em milhões') #texto lateral
plt.title('Valor da Produção de Peixes por Estado', y=1.075, x=0.815, bbox={'facecolor':'0.8', 'pad':5}) #texto superior
barra.set_xticks(ind) #espacamento entre barras ind la em cima
xtickNames = barra.set_xticklabels(listaUfs) #unidades inferiores (estados)
plt.setp(xtickNames, rotation=90, fontsize=10) #insercao dos textos inferiores em vertical
rects1 = barra.bar(ind, listaValores, width, color="navy") #insercao das barras
barra.set_position([0.1, 0.1, 0.85, 0.75]) #[left, bottom, width, height] tamanho e posicao do grafico
plt.savefig(('Bar-' + nomedosarquivos[2]).replace('txt', 'png'), dpi=300) #salva grafico em imagem png

'''------------------------------------------------------------------------------------------------------------------'''



#Importando Dados 3

arquivo = open(nomedosarquivos[3], 'r') 
linhas = arquivo.readlines()
arquivo.close()

listaPeixes = []
listaQuantidadesPeixes = []
for line in linhas: #Somatiza os valores por regiao e separa as informacoes do arquivo em 2 listas

    tipoPeixe = line.split(' ')[0] #separa por ' ' [0] = primeira palavra
    quantidadePeixe = line.split(' ')[1]
    listaPeixes.append(tipoPeixe) #adiciona siglauf na lista de ufs
    listaQuantidadesPeixes.append(int(quantidadePeixe)/1000) #dividiu em milhoes de reais 
    


#Grafico de Barras - Tipo do Peixe e Quantidade Total

fig = plt.figure(figsize=(10,6)) #criando uma imagem deste tamanho
barra = fig.add_subplot(111) #adicionando um grafico DE BARRAS

ind = np.arange(len(listaPeixes)) #Espacamento entre barras de estados len = qtas ufs tem
width = 0.4 #Largura da barra

t = int(max(listaQuantidadesPeixes))
t = int(t/1000)
t = t + 3
t = t * 1000 #Limite superior do valor (teto em escala de milhares) ta arredondando pra saber o teto

barra.set_xlim(-2*width,len(ind)) #limites laterais
barra.set_ylim(0, t) #limites inferior e superior
barra.set_ylabel('Quantidade em milhões') #texto lateral
plt.title('Total de Peixes por Tipo', y=1.075, x=0.815, bbox={'facecolor':'0.8', 'pad':5}) #texto superior
barra.set_xticks(ind) #espacamento entre barras ind la em cima
xtickNames = barra.set_xticklabels(listaPeixes) #unidades inferiores (estados)
plt.setp(xtickNames, rotation=90, fontsize=5) #insercao dos textos inferiores em vertical
rects1 = barra.bar(ind, listaQuantidadesPeixes, width, color="navy") #insercao das barras
barra.set_position([0.1, 0.17, 0.85, 0.7]) #[left, bottom, width, height] tamanho e posicao do grafico
plt.savefig(('Bar-' + nomedosarquivos[3]).replace('txt', 'png'), dpi=300) #salva grafico em imagem png

'''------------------------------------------------------------------------------------------------------------------'''



#Importando Dados 4

arquivo = open(nomedosarquivos[4], 'r') 
linhas = arquivo.readlines()
arquivo.close()

listaPeixes = []
listaValores = []
for line in linhas: #Somatiza os valores por regiao e separa as informacoes do arquivo em 2 listas

    tipoPeixe = line.split(' ')[0] #separa por ' ' [0] = primeira palavra
    valorPeixe = line.split(' ')[1]
    listaPeixes.append(tipoPeixe) #adiciona siglauf na lista de ufs
    listaValores.append(int(valorPeixe)/1000) #dividiu em milhoes de reais
    


#Grafico de Barras - Tipo do Peixe e Valor Total

fig = plt.figure(figsize=(10,6)) #criando uma imagem deste tamanho
barra = fig.add_subplot(111) #adicionando um grafico DE BARRAS

ind = np.arange(len(listaPeixes)) #Espacamento entre barras de estados len = qtas ufs tem
width = 0.4 #Largura da barra

t = int(max(listaValores))
t = int(t/1000)
t = t + 1
t = t * 1000 #Limite superior do valor (teto em escala de milhares) ta arredondando pra saber o teto

barra.set_xlim(-2*width,len(ind)) #limites laterais
barra.set_ylim(0, t) #limites inferior e superior
barra.set_ylabel('Valor em milhões') #texto lateral
plt.title('Valor da Produção de Peixes por Tipo', y=1.075, x=0.815, bbox={'facecolor':'0.8', 'pad':5}) #texto superior
barra.set_xticks(ind) #espacamento entre barras ind la em cima
xtickNames = barra.set_xticklabels(listaPeixes) #unidades inferiores (estados)
plt.setp(xtickNames, rotation=90, fontsize=5) #insercao dos textos inferiores em vertical
rects1 = barra.bar(ind, listaValores, width, color="navy") #insercao das barras
barra.set_position([0.1, 0.17, 0.85, 0.7]) #[esquerda, baixo, width, height] tamanho e posicao do grafico
plt.savefig(('Bar-' + nomedosarquivos[4]).replace('txt', 'png'), dpi=300) #salva grafico em imagem png

'''------------------------------------------------------------------------------------------------------------------'''



#Importando Dados 5

arquivo = open(nomedosarquivos[5], 'r') 
linhas = arquivo.readlines()
arquivo.close()

listaAnos = []
listaQuantidades = []
for line in linhas: #Somatiza os valores por regiao e separa as informacoes do arquivo em 2 listas

    ano = line.split(' ')[0] #separa por ' ' [0] = primeira palavra
    quantidadesAno = line.split(' ')[1]
    listaAnos.append(ano) #adiciona siglauf na lista de ufs
    listaQuantidades.append(int(quantidadesAno)/1000) #dividiu em milhoes de reais
    


#Grafico de Barras - Ano e Quantidade Total

fig = plt.figure(figsize=(10,6)) #criando uma imagem deste tamanho
barra = fig.add_subplot(111) #adicionando um grafico DE BARRAS

ind = np.arange(len(listaAnos)) #Espacamento entre barras de estados len = qtas ufs tem
width = 0.4 #Largura da barra

t = int(max(listaQuantidades))
t = int(t/1000)
t = t + 3
t = t * 1000 #Limite superior do valor (teto em escala de milhares) ta arredondando pra saber o teto

barra.set_xlim(-2*width,len(ind)) #limites laterais
barra.set_ylim(0, t) #limites inferior e superior
barra.set_ylabel('Quantidade em milhões') #texto lateral
plt.title('Total de Peixes por Ano', y=1.075, x=0.815, bbox={'facecolor':'0.8', 'pad':5}) #texto superior
barra.set_xticks(ind) #espacamento entre barras ind la em cima
xtickNames = barra.set_xticklabels(listaAnos) #unidades inferiores (estados)
plt.setp(xtickNames, rotation=90, fontsize=10) #insercao dos textos inferiores em vertical
rects1 = barra.bar(ind, listaQuantidades, width, color="navy") #insercao das barras
barra.set_position([0.1, 0.1, 0.85, 0.75]) #[left, bottom, width, height] tamanho e posicao do grafico
plt.savefig(('Bar-' + nomedosarquivos[5]).replace('txt', 'png'), dpi=300) #salva grafico em imagem png

'''------------------------------------------------------------------------------------------------------------------'''



#Importando Dados 6

arquivo = open(nomedosarquivos[6], 'r') 
linhas = arquivo.readlines()
arquivo.close()

listaAnos = []
listaValores = []
for line in linhas: #Somatiza os valores por regiao e separa as informacoes do arquivo em 2 listas

    ano = line.split(' ')[0] #separa por ' ' [0] = primeira palavra
    valoresAno = line.split(' ')[1]
    listaAnos.append(ano) #adiciona siglauf na lista de ufs
    listaValores.append(int(valoresAno)/1000) #dividiu em milhoes de reais
    


#Grafico de Barras - Ano e Valor Total

fig = plt.figure(figsize=(10,6)) #criando uma imagem deste tamanho
barra = fig.add_subplot(111) #adicionando um grafico DE BARRAS

ind = np.arange(len(listaAnos)) #Espacamento entre barras de estados len = qtas ufs tem
width = 0.4 #Largura da barra

t = int(max(listaValores))
t = int(t/1000)
t = t + 1
t = t * 1000 #Limite superior do valor (teto em escala de milhares) ta arredondando pra saber o teto

barra.set_xlim(-2*width,len(ind)) #limites laterais
barra.set_ylim(0, t) #limites inferior e superior
barra.set_ylabel('Valores em milhões') #texto lateral
plt.title('Valor da Produção de Peixes por Ano', y=1.075, x=0.815, bbox={'facecolor':'0.8', 'pad':5}) #texto superior
barra.set_xticks(ind) #espacamento entre barras ind la em cima
xtickNames = barra.set_xticklabels(listaAnos) #unidades inferiores (estados)
plt.setp(xtickNames, rotation=90, fontsize=10) #insercao dos textos inferiores em vertical
rects1 = barra.bar(ind, listaValores, width, color="navy") #insercao das barras
barra.set_position([0.1, 0.1, 0.85, 0.75]) #[left, bottom, width, height] tamanho e posicao do grafico
plt.savefig(('Bar-' + nomedosarquivos[6]).replace('txt', 'png'), dpi=300) #salva grafico em imagem png
