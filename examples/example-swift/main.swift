//
//  main.swift
//  FileFiller-swift
//
//  Created by Clovis Durand on 14/04/2020.
//  Copyright © 2020 Clovis Durand. All rights reserved.
//

import Foundation

func printUsage() -> Void {
    let lExecutableName = (CommandLine.arguments[0] as NSString).lastPathComponent

    print("[USAGE] \(lExecutableName)");
    print("        <arg1> - Input file path");
    print("        <arg2> - Output file path");
    print("        <arg3> - Tag mapping file path");
}

func main() -> Void {
    if(4 != CommandLine.argc || ("--help" == CommandLine.arguments[1])) {
        printUsage();
        exit(EXIT_FAILURE);
    }

    let lResult: (Int32, String) = FileFiller.parseFile(inputFilePath: CommandLine.arguments[1], outputFilePath: CommandLine.arguments[2], tagFilePath: CommandLine.arguments[3], allocationSize: 4096);

    if(0 > lResult.0) {
        print("[ERROR] FileFiller.parseFile replaced \(lResult) tags.");
        print("        Got string : ");
        print(lResult.1);
    }

    exit(EXIT_SUCCESS);
}

main();
