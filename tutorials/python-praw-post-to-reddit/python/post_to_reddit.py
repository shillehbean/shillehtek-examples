# Authenticates to Reddit using PRAW and submits a text post (self post) to a specified subreddit.
#
# Full tutorial: https://shillehtek.com/blogs/news/python-praw-post-to-reddit
# Shop parts: https://shillehtek.com
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import praw

# Reddit API credentials
reddit = praw.Reddit(
    client_id='your_client_id',
    client_secret='your_client_secret',
    user_agent='your_app_name',
    username='your_reddit_username',
    password='your_reddit_password'
)

# Subreddit to post to
subreddit_name = "test"  # Change to your desired subreddit

# Title and content of the post
title = "My first automated post using Python!"
selftext = "Hello Reddit! This post was made using a Python script."

# Submit the post
subreddit = reddit.subreddit(subreddit_name)
subreddit.submit(title=title, selftext=selftext)

print(f"Posted to Reddit: {title}")
