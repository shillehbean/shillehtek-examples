# Create an Amazon ECR repository named my-lambda-repo in us-east-1.
#
# Full tutorial: https://shillehtek.com/blogs/news/aws-lambda-docker-install-pip-ecr
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

aws ecr create-repository --repository-name my-lambda-repo --region us-east-1
