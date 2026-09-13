# AWS Lambda function that receives an event containing MPU6050 data and writes the point_number, ax value (as a Decimal) and topic into the DynamoDB table named 'MPU6050'.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mpu6050-send-data-dynamodb
# Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
#             https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import boto3
from decimal import Decimal
import logging

# Configure the logging module
logger = logging.getLogger()
logger.setLevel(logging.INFO)

dynamodb = boto3.resource('dynamodb')
table_name = 'MPU6050'
table = dynamodb.Table(table_name)

def lambda_handler(event, context):
    # Log information using the logging module
    logger.info("EVENT")

    ax = Decimal(event['value'])
    topic = event['topic']
    point_number = event['point_number']

    logger.info(point_number)

    # Write to DynamoDB
    table.put_item(
        Item={
            'point_number': point_number,
            'ax': ax,
            'topic': topic
        }
    )

    logger.info('Done Inputting')
