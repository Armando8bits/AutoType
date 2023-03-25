'''version 2.4.0 automaticamente se devuelve a la entana anterior y coloc el texto sin perder tiempo
	version 2.3 se adicionaron botones de copiar y pegar
	version 2.2 interfaz grafica :´) y en teoria es mas facil de colocar texto en pantalla.
	version 1, era en linea de comandos y uno tenia que cambiar la variable con el texto a colocar, y esparar 2 segundos para colocar texto, tiempo para que usuario coloque cursor en app de destino

ejecutalo con este comando: 
 		exec(open("D:\colocatexto2.py").read())
'''
import pyautogui as pg #"pip install PyAutoGUI" si no esta instalada
import time
from tkinter import *
from tkinter import messagebox
#import pyperclip #pip install pyperclip #para trabajar con portapapeles
root = Tk()
root.attributes('-topmost', True) #mantiene siempre la ventana en primer plano
root.title("Coloca Texto 2.4.0")
root.geometry("296x290")
root.resizable(0, 0)

def pulsar_boton():
	#print("pulsate este!\n")
	if(verifica_vacio_caja()):#si la caja de texto está vacia no trabaja
		Opcion=messagebox.askyesno(message="¿Seguro de escribir ese texto?\n\nSi acepta considere que no se copiaran caracteres especiales del idioma español (á,é,í,ó,ú,¿,etc.) Adicionalmente el texto se colocará en el cursor de la ultima ventana activa.", title="Confirma para confirmar")
		if(Opcion==True):
			pg.hotkey("alt", "tab") #se cambia a la ventana anterior sin perder tiempo
			time.sleep(0.5) #numero de segundos para que coloques el cursor para q se cloque la siguiente linea
			pg.typewrite(cajadetexto.get(1.0, 'end')) #hace la magia 
			messagebox.showinfo(message="Exito al tipear texto solicitado!", title="Mensaje")

def limpiar_Caja():
	#print("limpiate este!")
	cajadetexto.delete(1.0, 'end')

def pegar_Caja():
	pg.hotkey("ctrl", "v") #simplemente uso eso para no programar nada con el portapapeles

def copia_Caja():
	#print("copiate este!")
	if(verifica_vacio_caja()):#si la caja de texto está vacia no trabaja
		pg.hotkey("ctrl", "a")#selecciona todo el texto
		pg.hotkey("ctrl", "c") #manda a copiar
		pg.press('left') #mueve una tecla para des-selecionar todo

def verifica_vacio_caja():
	StrTexto=cajadetexto.get(1.0, 'end')
	'''In this syntax, 1.0 is the starting position and the end keyword refers to the end of the document.
	that means all the data will be fetched from the Text box. '''
	if(len(StrTexto)>1):
		respuesta=True
	else:
		respuesta=False
	return respuesta

Label(root,text="Presione CTRL+V para pegar desde el portapapeles").pack()
# Add a Scrollbar(horizontal)
v=Scrollbar(root, orient='vertical')
v.pack(side=RIGHT, fill='y')
#caja de texto
cajadetexto=Text(root, height=13, width=33, yscrollcommand=v.set)#alto y ancho, vincula con scrollbar
v.config(command=cajadetexto.yview)## Attach the scrollbar with the text widget
cajadetexto.focus_set()
cajadetexto.pack()
''' se crea una variable contenedora del txtbox para
asi manejar el setfocus
text.insert(INSERT, "asi se inserta texto desde codigo")
'''
#botones
Button(root, text="Pegar",command=pegar_Caja).pack(side=RIGHT)
Button(root, text="Copiar",command=copia_Caja).pack(side=RIGHT)
Button(root, text="Tipear Texto",command=pulsar_boton,width=19).pack(side=LEFT)
'''se llama a la funcionsin los parentesis, ya que si los pones, no se
ejecuta cuando quiere, y solo una vez al cargar la ventana'''
Button(root, text="Limpiar",command=limpiar_Caja).pack(side=RIGHT)
Label(root,text="Creado por: Armando Ramirez",fg= "gray51").pack(after=cajadetexto)
mainloop()