# Authenticate Docker to the specified ECR registry using the AWS CLI get-login-password command.
#
# Full tutorial: https://shillehtek.com/blogs/news/aws-lambda-docker-install-pip-ecr
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

aws ecr get-login-password --region us-east-1 | docker login --username AWS --password-stdin <aws_account_id>.dkr.ecr.us-east-1.amazonaws.com
