# Update the specified AWS Lambda function to use the image stored in ECR.
#
# Full tutorial: https://shillehtek.com/blogs/news/aws-lambda-docker-install-pip-ecr
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

aws lambda update-function-code --function-name my-lambda-function --image-uri <aws_account_id>.dkr.ecr.us-east-1.amazonaws.com/my-lambda-repo:latest
