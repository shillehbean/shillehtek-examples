# Shell commands to tag the built image for ECR, authenticate Docker to ECR, and push the image to the specified ECR repository.
#
# Full tutorial: https://shillehtek.com/blogs/news/aws-lambda-selenium-chromedriver-headless-automation
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

docker tag selenium-chrome-driver <your amazon account id>.dkr.ecr.us-east-1.amazonaws.com/docker-images:v1.0.0

aws ecr get-login-password --region us-east-1 | docker login --username AWS --password-stdin <your amazon account id>.dkr.ecr.us-east-1.amazonaws.com/docker-images

docker push <your amazon account id>.dkr.ecr.us-east-1.amazonaws.com/docker-images:v1.0.0
