from pulsar import OptionType

#Stuff common to many modules
c_mod,e2base,modpath="c_module","TwoElectronIntegral","pulsar_libint.so"
e1base,version="OneElectronIntegral","0.1a"
no_options={}
no_ref,Ben,Ryan=[""],["Ryan Richard"]

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
