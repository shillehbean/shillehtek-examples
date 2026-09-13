# Push the tagged Docker image to the target Amazon ECR repository.
#
# Full tutorial: https://shillehtek.com/blogs/news/aws-lambda-docker-install-pip-ecr
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

docker push <aws_account_id>.dkr.ecr.us-east-1.amazonaws.com/my-lambda-repo:latest
