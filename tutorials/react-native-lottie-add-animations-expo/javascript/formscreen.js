// A React Native screen component that shows a simple name/email form and, after submission, displays a thank-you message with a Lottie animation.
//
// Full tutorial: https://shillehtek.com/blogs/news/react-native-lottie-add-animations-expo
// Shop parts: https://shillehtek.com
// More examples: https://github.com/shillehbean/shillehtek-examples
//

import React, { useState } from 'react';
import { View, TextInput, Button, StyleSheet, Text } from 'react-native';
import LottieView from 'lottie-react-native';

const FormScreen = () => {
  const [submitted, setSubmitted] = useState(false);

  const handleSubmit = () => {
    setSubmitted(true);
  };

  return (
    <View style={styles.container}>
      {!submitted ? (
        <View style={styles.formContainer}>
          <TextInput style={styles.input} placeholder="Name" />
          <TextInput style={styles.input} placeholder="Email" />
          <Button title="Submit" onPress={handleSubmit} />
        </View>
      ) : (
        <View style={{alignItems: 'center'}}>
         <Text style={{top: 200, fontSize: 20, fontWeight: 'bold'}}>Thank You For Submitting</Text> 
          <LottieView
            source={require('./assets/animation.json')}
            autoPlay
            loop={false}
            style={{flexGrow: 1, width: 400}}
          />
        </View>
      )}
    </View>
  );
};

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  formContainer: {
    width: '80%',
  },
  input: {
    height: 40,
    borderColor: 'gray',
    borderWidth: 1,
    marginBottom: 10,
    padding: 8,
  },
});

export default FormScreen;
