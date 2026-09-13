# Tag the local Docker image for the target ECR repository with the account-specific registry URI.
#
# Full tutorial: https://shillehtek.com/blogs/news/aws-lambda-docker-install-pip-ecr
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

docker tag my-lambda-image <aws_account_id>.dkr.ecr.us-east-1.amazonaws.com/my-lambda-repo:latest
