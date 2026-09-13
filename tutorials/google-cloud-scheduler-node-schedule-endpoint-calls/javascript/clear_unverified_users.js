// Express POST endpoint that deletes unverified users with zero credits after validating a secret in the request body.
//
// Full tutorial: https://shillehtek.com/blogs/news/google-cloud-scheduler-node-schedule-endpoint-calls
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

app.post('/clearUnverifiedUsers', async (req, res) => {
  try {
    const secret = req.body.secret;
    if (secret !== 'password') {
      return res.status(403).json({ message: `Body ${secret}` });
    }
    
    const result = await signinTable.deleteMany({ verified: false, credits: 0 });
    return res.json({ message: 'Users cleared successfully', deletedCount: result.deletedCount });
  } catch (error) {
    return res.status(500).json({ error: 'Internal Server Error' });
  }
});
