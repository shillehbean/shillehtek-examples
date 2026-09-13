# Multi-stage Dockerfile that installs Python pip packages into the Lambda /var/task directory and produces a final Lambda container image with handler.py.
#
# Full tutorial: https://shillehtek.com/blogs/news/aws-lambda-docker-install-pip-ecr
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Builder stage - you can use other AWS runtimes and python versions
FROM public.ecr.aws/lambda/python:3.12-x86_64 as builder

# Install Python packages (replace as needed)
RUN pip install --no-cache-dir requests numpy pandas --target "/var/task"

# Final stage
FROM public.ecr.aws/lambda/python:3.12-x86_64

# Copy necessary files from the builder stage - add whatever code you need
COPY --from=builder /var/task /var/task
COPY handler.py ./

# Set the CMD to your handler
CMD ["handler.lambda_handler"]
