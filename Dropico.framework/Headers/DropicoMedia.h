//
//  DropicoMedia.h
//
//  Created by Shai Mishali on 11/15/11.
//  Copyright (c) 2011 Dropico Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Dropico.h"

/**
 `DropicoMedia` handles everything related to retrieving or uploading media from/to the Dropico Server.
 */

@interface DropicoMedia : NSObject{}

///----------------------------
/// @name Retreiving Media
///----------------------------

/**
 Get all photo albums for a specific service
 
 @param service Service to get photo albums from
 @param success Request success block - Response should include an array of `DropicoAlbum` objects
 @param failure Request failure block
 
 @return An array of `DropicoAlbum` objects
 */

+ (void) getAlbums: (NSString*)service
           success:(void (^)(DropicoResponse *response))success
           failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Get photos from a specific album in a specific service
 
 @param service Service to get photos from
 @param albumId Album ID in the requested service, from which you wish to retrieve the photo
 @param success Request success block - Response should include an array of `DropicoMediaItem` objects
 @param failure Request failure block
 
 @return An array of `DropicoMediaItem` objects
 */

+ (void) getPhotos: (NSString*)service
           albumId:(NSString *)albumId
           success:(void (^)(DropicoResponse *response))success
           failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

///-----------------------------
/// @name Uploading Media
///-----------------------------

/**
 Upload a raw NSData photo to various Social/Photo services
 
 @param data NSData object of image data
 @param services An array of services to which the photo should be uploaded
 @param title Title of the uploaded photo
 @param description Description of the uploaded photo
 @param location Location in which the uploaded photo was taken
 @param venueID Venue in which the uploaded photo was taken
 @param filters An array of filters used on the uploaded photo
 @param feedOnly Set to `YES` to post a feed instead of a physical upload, on services where its available
 @param meta Additional meta data
 @param progressCallback A block function which is being called on every update to the proress of the upload.
 - `bytesWritten` - Number of bytes written in the current chunk
 - `totalBytesWritten` - Total bytes written to the server so far
 - `totalBytesExpectedToWrite` - Total bytes expected to be written to the server (Actually, the file size)
 @param success Request success block - Response should include an NSDictionary object containing information about the upload
 @param failure Request failure block
 
 @warning *Important:* Calling this method actually performs 2 API calls to the Dropico API Server, the first one to prepare the upload and the second one to actually perform it.
 
 You could let the user "move on" after the first step completed (You can know when the first step ended by checking when the upload to the server ended).
 
 @return If services is nil, an NSURL object with the dropi.co shorturl, otherwise A Dictionary containing information about the upload.
 */

+ (void) uploadRawPhoto:(NSData *) data
               services:(NSArray *)services
                  title:(NSString *)title
            description:(NSString *)description
               location:(CLLocation *)location
                venueID:(NSString *)venueID
                filters:(NSArray *)filters
               feedOnly:(BOOL)feedOnly
                   meta:(NSDictionary *)meta
 uploadProgressCallback:(void (^)(NSUInteger bytesWritten, long long totalBytesWritten, long long totalBytesExpectedToWrite))progressCallback
                success:(void (^)(DropicoResponse *response))success
                failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Upload a binary photo to various Social/Photo services
 
 @param photo Photo to upload
 @param services An array of services to which the photo should be uploaded
 @param title Title of the uploaded photo
 @param description Description of the uploaded photo
 @param location Location in which the uploaded photo was taken
 @param venueID Venue in which the uploaded photo was taken
 @param filters An array of filters used on the uploaded photo
 @param feedOnly Set to `YES` to post a feed instead of a physical upload, on services where its available
 @param meta Additional meta data
 @param progressCallback A block function which is being called on every update to the proress of the upload.
    - `bytesWritten` - Number of bytes written in the current chunk
    - `totalBytesWritten` - Total bytes written to the server so far
    - `totalBytesExpectedToWrite` - Total bytes expected to be written to the server (Actually, the file size)
 @param success Request success block - Response should include an NSDictionary object containing information about the upload
 @param failure Request failure block
 
 @warning *Important:* Calling this method actually performs 2 API calls to the Dropico API Server, the first one to prepare the upload and the second one to actually perform it.
 
 You could let the user "move on" after the first step completed (You can know when the first step ended by checking when the upload to the server ended).
 
 @return If services is nil, an NSURL object with the dropi.co shorturl, otherwise A Dictionary containing information about the upload.
 */
+ (void) uploadPhoto: (UIImage *) photo
            services:(NSArray *)services
               title:(NSString *)title
         description:(NSString *)description
            location:(CLLocation *)location
             venueID:(NSString *)venueID
             filters:(NSArray *)filters
            feedOnly:(BOOL)feedOnly
                meta:(NSDictionary *)meta
uploadProgressCallback:(void (^)(NSUInteger bytesWritten, long long totalBytesWritten, long long totalBytesExpectedToWrite))progressCallback
             success:(void (^)(DropicoResponse *response))success
             failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Upload a photo to a Social/Photo service directly from an external URL
 
 @param url URL to upload photo from
 @param service A service to upload the photo to
 @param albumID The Album ID in the specific service to which you want to upload the photo
 @param title The title of the uploaded photo
 @param description The description of the uploaded photo
 @param success Request success block
 @param failure Request failure block
 
 @return BOOL `YES`
 */

+ (void) uploadPhotoFromURL: (NSURL *) url
                    service:(NSString *)service
                    albumID:(NSString *)albumID
                      title:(NSString *)title
                description:(NSString *)description
                    success:(void (^)(DropicoResponse *response))success
                    failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

/**
 Create a new empty album in one of the user's services
 
 @param service The service for which you want to create a new album
 @param title A name for the newly created album
 @param description A description for the newly created album
 @param success Request success block - Response should include a `DropicoAlbum` object
 @param failure Request failure block
 
 @returns A `DropicoAlbum` object
 */
+ (void) createAlbum: (NSString*)service
               title:(NSString *)title
         description:(NSString *)description
             success:(void (^)(DropicoResponse *response))success
             failure:(void (^)(NSURLRequest *request, DropicoResponse *response, NSError *error))failure;

@end