##############################################################################
#copyright 2012, Hamid MEDJAHED  (hmedjahed@prologue.fr) Prologue            #
#Licensed under the Apache License, Version 2.0 (the "License");             #
#you may not use this file except in compliance with the License.            #
#You may obtain a copy of the License at                                     #
#                                                                            #
#       http://www.apache.org/licenses/LICENSE-2.0                           #
#                                                                            #
#Unless required by applicable law or agreed to in writing, software         #
#distributed under the License is distributed on an "AS IS" BASIS,           #
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.    #
#See the License for the specific language governing permissions and         #
#limitations under the License.                                              #
##############################################################################
#!/usr/bin/env python
# -*- coding: latin-1 -*-

import sys
import pypacksrc
srcdirectory=pypacksrc.srcpydir+"/pyaccords"
sys.path.append(srcdirectory)
from ec2configAction import *
from actionClass import *

def current(categStr):
	l=categStr.split(",")
	categoryAtr = Cec2config(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8],l[9],l[10],l[11] )
	resCateg = ec2config_current(categoryAtr)
	restResp = [str(restCateg.status),str(restCateg.message)]	restResponse = ",".join(restResp)
	return restResponse

