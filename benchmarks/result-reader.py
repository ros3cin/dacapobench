import sys

class Result:
    def __init__(self,elapsedTime=0,cpuConsumption=0,packageConsumption=0,dramConsumption=0):
        self.elapsedTime = elapsedTime
        self.cpuConsumption = cpuConsumption
        self.packageConsumption = packageConsumption
        self.dramConsumption = dramConsumption


if not len(sys.argv) > 1:
    print('Please, inform the filename')
else:
    fileName = sys.argv[1]
    print('Filename: '+fileName)
    with open(fileName) as f:
        lines = f.readlines()
    
    gotElapsedTime = False
    gotCpu = False
    gotPackage = False
    gotDram = False

    results = []

    curr = Result()
    for line in lines:
        if not gotElapsedTime:
            if ("PASSED" in line) or ("completed" in line):
                curr.elapsedTime = line.split(' ')[6]
                gotElapsedTime = True
        elif not gotDram:
            if "joules in dram" in line:
                curr.dramConsumption = line.split(' ')[1]
                gotDram = True
        elif not gotCpu:
            if "joules in cpu" in line:
                curr.cpuConsumption = line.split(' ')[1]
                gotCpu = True
        elif not gotPackage:
            if "joules on package" in line:
                curr.packageConsumption = line.split(' ')[1]
                gotPackage = True
        if gotElapsedTime and gotCpu and gotPackage:
                results.append(curr)
                curr = Result()
                gotElapsedTime = False
                gotCpu = False
                gotPackage = False
                gotDram = False
    print('Finished reading')

    elapsedTimes = map(lambda result: result.elapsedTime, results)
    elapsedTimesStr  = ','.join(map(str,elapsedTimes))
    elapsedTimesCsv = open('elapsedTimes.csv','w')
    elapsedTimesCsv.write(elapsedTimesStr)
    print('Elapsed times csv created')

    cpuConsumptions = map(lambda result: result.cpuConsumption, results)
    cpuConsumptionsStr = ','.join(map(str,cpuConsumptions))
    cpuConsumptionsCsv = open('cpuConsumptions.csv','w')
    cpuConsumptionsCsv.write(cpuConsumptionsStr)
    print('Cpu consumptions csv created')

    dramConsumptions = map(lambda result: result.dramConsumption, results)
    dramConsumptionsStr = ','.join(map(str,dramConsumptions))
    dramConsumptionsCsv = open('dramConsumptions.csv','w')
    dramConsumptionsCsv.write(dramConsumptionsStr)
    print('Dram consumptions csv created')

    packageConsumptions = map(lambda result: result.packageConsumption, results)
    packageConsumptionsStr = ", ".join(map(str,packageConsumptions))
    packageConsumptionsCsv = open('packageConsumptions.csv','w')
    packageConsumptionsCsv.write(packageConsumptionsStr)
    print('Package consumptions csv created')
   
    print('Number of results: '+str(len(results)))
