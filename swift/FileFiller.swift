//
//  FileFiller-swift.swift
//  FileFiller-swift
//
//  Created by Clovis Durand on 15/04/2020.
//  Copyright © 2020 Clovis Durand. All rights reserved.
//

import Foundation

class FileFiller {
    public static func parseString(input: String, tags: String, allocationSize: Int) -> (Int32, String) {
        let lInputCString: UnsafePointer<CChar> = (input as NSString).utf8String!;
        let lTagCString:   UnsafePointer<CChar> = (tags  as NSString).utf8String!;

        let lOutputCString: UnsafeMutablePointer<CChar>? = UnsafeMutablePointer<CChar>.allocate(capacity: allocationSize);

        let lResult: Int32 = FileFiller_parseString(lInputCString, lTagCString, lOutputCString);

        let lOutputSwiftString: String = String(cString: lOutputCString!);

        if(0 > lResult) {
            print(stderr, "[ERROR] FileFiller_parseFile failed\n");
            exit(EXIT_FAILURE);
        } else {
            print("[DEBUG] <FileFiller::parseString> FileFiller_parseString replaced \(lResult) tags\n");
            print("[DEBUG] <FileFiller::parseString> Got string :\n\(lOutputSwiftString)\n");
        }

        return (lResult, lOutputSwiftString);
    }

    public static func parseFile(inputFilePath: String, outputFilePath: String, tagFilePath: String, allocationSize: Int) -> (Int32, String) {
        /* Set the file path variables */
        let lInputFilePath: UnsafePointer<CChar>      = (inputFilePath as NSString).utf8String!;
        let lOutputFilePath: UnsafePointer<CChar>     = (outputFilePath as NSString).utf8String!;
        let lTagMappingFilePath: UnsafePointer<CChar> = (tagFilePath as NSString).utf8String!;

        let lOutputCString: UnsafeMutablePointer<CChar>? = UnsafeMutablePointer<CChar>.allocate(capacity: allocationSize);

        let lResult: Int32 = FileFiller_parseFile(lTagMappingFilePath, lInputFilePath, lOutputFilePath, lOutputCString);

        let lOutputSwiftString: String = String(cString: lOutputCString!);
        if(0 > lResult) {
            print(stderr, "[ERROR] FileFiller_parseFile failed\n");
            exit(EXIT_FAILURE);
        } else {
            print("[DEBUG] <FileFiller::parseFile> FileFiller_parseFile replaced \(lResult) tags\n");
            print("[DEBUG] <FileFiller::parseFile> Got string :\n\(lOutputSwiftString)\n");
        }

        return (lResult, lOutputSwiftString);
    }
}
