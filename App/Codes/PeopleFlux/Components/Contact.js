import React from 'react'
import { StyleSheet, View, TextInput, Text , Platform  } from 'react-native'
import {KeyboardAwareScrollView} from 'react-native-keyboard-aware-scrollview'
import BoutonEnvoyer from './BoutonEnvoyer'




class Contact extends React.Component {

  constructor(props) {
     super(props);
     this.state = { text: 'Votre email',};
     this.sujet = { text: 'Votre sujet'};
     this.message = { text : 'Votre message'}
   }

  render() {
    return (

          <KeyboardAwareScrollView
            style={styles.main_container}
            enableOnAndroid={true}
            enableAutomaticScroll={(Platform.OS === 'ios')}
          >
                <Text style={styles.text_contact}>Contact</Text>
                <Text style={styles.text_que_souhaitez_vous}>Que souhaitez vous?</Text>
                <Text style={styles.champ_mail}>Email</Text>

                <TextInput
                  style={styles.bordure_mail}
                  onChangeText={(text) => this.setState({text})}
                  placeholder='Votre email'
                  placeholderTextColor='#232531'
                  returnKeyType = {"next"}
                  onSubmitEditing={() => { this.secondTextInput.focus(); }}
                  blurOnSubmit={false}
                />

                <Text style={styles.champ_sujet}>Sujet</Text>
                <TextInput
                  ref={(input) => { this.secondTextInput = input; }}
                  style={styles.bordure_sujet}
                  onChangeText={(text) => this.setState({text})}
                  placeholder='Votre sujet'
                  placeholderTextColor='#232531'
                  returnKeyType = {"next"}
                  onSubmitEditing={() => { this.thirdTextInput.focus(); }}
                  blurOnSubmit={false}

                />

                <Text style={styles.champ_message}>Message</Text>
                <TextInput
                ref={(input) => { this.thirdTextInput = input; }}
                  style={styles.bordure_message}
                  onChangeText={(text) => this.setState({text})}
                  placeholder='Votre message'
                  placeholderTextColor='#232531'
                />
                <BoutonEnvoyer/>

              </KeyboardAwareScrollView>


    )
  }
}

const styles = StyleSheet.create({
  main_container: {
    flex: 1,
    backgroundColor: '#232531',

  },
  text_contact:{
    fontSize:30,
    color:'#c70039',
    marginLeft:10,
    marginTop:10
  },
  text_que_souhaitez_vous:{
    fontSize:20,
    color:'white',
    marginLeft:10,
    marginTop:5
  },
  champ_mail:{
    fontSize:20,
    color :'white',
    marginLeft:15,
    marginTop:18,
  },
  champ_sujet:{
    fontSize:20,
    color :'white',
    marginLeft:15,
    marginTop:1,
  },
  champ_message:{
    fontSize:20,
    color :'white',
    marginLeft:15,
    marginTop:20,
  },
  bordure_mail:{
    height: 35,
    borderColor: '#4B4C56',
    marginBottom:18,
    marginLeft:6,
    marginRight:6,
    borderWidth: 1,
    borderRadius:25,
    overflow: 'hidden',
    backgroundColor: '#4B4C56',
    color: '#fff',
    paddingLeft: 7,

  },
  bordure_sujet:{
    height: 35,
    borderColor: '#4B4C56',
    marginTop: 1,
    marginLeft:6,
    marginRight:6,
    borderWidth: 1,
    borderRadius:25,
    overflow: 'hidden',
    backgroundColor: '#4B4C56',
    color: '#fff',
    paddingLeft: 7,


  },
  bordure_message:{
    height: 90,
    borderColor: '#4B4C56',
    marginTop: 1,
    marginLeft:6,
    marginRight:6,
    borderWidth: 1,
    borderRadius:25,
    backgroundColor: '#4B4C56',
    color: '#fff',
    paddingLeft: 7,

  }



})

export default Contact
