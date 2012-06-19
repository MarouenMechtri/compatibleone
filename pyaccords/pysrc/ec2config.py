#!/usr/bin/env python
# -*- coding: latin-1 -*-
# Hamid MEDJAHED (c) Prologue
import sys
import pypacksrc
srcdirectory=pypacksrc.srcpydir+"/pyaccords"
sys.path.append(srcdirectory)
from ec2configInterface import *

def create(categStr):
	l=categStr.split(",")
	categInterf = Cec2config(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8],l[9],l[10],l[11] )
	resCateg = ec2config_create(categInterf)
	categStrR = [ str(resCateg.name),str(resCateg.description),str(resCateg.accesskey),str(resCateg.secretkey),str(resCateg.authenticate),str(resCateg.agent),str(resCateg.host),str(resCateg.version),str(resCateg.namespace),str(resCateg.base),str(resCateg.tls),str(resCateg.current) ]
	categStrNew = ",".join(categStrR)
	return categStrNew

def retrieve(categStr):
	l=categStr.split(",")
	categInterf = Cec2config(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8],l[9],l[10],l[11] )
	resCateg = ec2config_retrieve(categInterf)
	categStrR = [ str(resCateg.name),str(resCateg.description),str(resCateg.accesskey),str(resCateg.secretkey),str(resCateg.authenticate),str(resCateg.agent),str(resCateg.host),str(resCateg.version),str(resCateg.namespace),str(resCateg.base),str(resCateg.tls),str(resCateg.current) ]
	categStrNew = ",".join(categStrR)
	return categStrNew

def update(categStr):
	l=categStr.split(",")
	categInterf = Cec2config(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8],l[9],l[10],l[11] )
	resCateg = ec2config_update(categInterf)
	categStrR = [ str(resCateg.name),str(resCateg.description),str(resCateg.accesskey),str(resCateg.secretkey),str(resCateg.authenticate),str(resCateg.agent),str(resCateg.host),str(resCateg.version),str(resCateg.namespace),str(resCateg.base),str(resCateg.tls),str(resCateg.current) ]
	categStrNew = ",".join(categStrR)
	return categStrNew

def delete(categStr):
	l=categStr.split(",")
	categInterf = Cec2config(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8],l[9],l[10],l[11] )
	resCateg = ec2config_delete(categInterf)
	categStrR = [ str(resCateg.name),str(resCateg.description),str(resCateg.accesskey),str(resCateg.secretkey),str(resCateg.authenticate),str(resCateg.agent),str(resCateg.host),str(resCateg.version),str(resCateg.namespace),str(resCateg.base),str(resCateg.tls),str(resCateg.current) ]
	categStrNew = ",".join(categStrR)
	return categStrNew

