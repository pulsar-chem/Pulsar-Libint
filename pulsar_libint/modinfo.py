from pulsar import OptionType

#Stuff common to many modules
c_mod,e2base,modpath="c_module","TwoElectronIntegral","pulsar_libint.so"
e1base,version="OneElectronIntegral","0.1a"
no_options={}
no_ref,Ryan=[""],["Ryan Richard"]

mods=[["Kinetic","Overlap","NuclearElectron"],
      ["ERI"]]
minfo={}
for i in range(2):
    for mod in mods[i]:
        minfo[mod]={
            "type":c_mod,
            "base":e1base if i==0 else e2base,
            "modpath":modpath,
            "version":version,
            "authors":Ryan,
            "refs":no_ref,
            "options":no_options}
cif="Computes integrals for the"
minfo["Kinetic"]["description"]=cif+" kinetic energy of the electrons"
minfo["Overlap"]["description"]=cif+" overlap of two one electron basis sets"
minfo["NuclearElectron"]["description"]=cif+"nuclear-electron attraction"
minfo["ERI"]["description"]=cif+" electron-electron repulsion integrals"
minfo["ERI"]["options"]={
   "THRESHOLD":(OptionType.Float,0.0,False,None,
       "Blocks of integrals below this threshold will be discarded")
}
