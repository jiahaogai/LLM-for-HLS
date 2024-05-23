import subprocess

import streamlit as st
from openai import OpenAI

class HLSCoderApp:
    def __init__(self, api_key, base_url):
        self.client = OpenAI(api_key=api_key, base_url=base_url)
        # st.session_state.block_list = []
        self.setup_ui()

    def setup_ui(self):
        self.style_main_header()
        self.setup_sidebar()
        self.initialize_session_state()
        self.display_chat_history()
        placeholder = self.handle_prompt_input()
        if placeholder is not None:
            st.session_state.placeholder = placeholder
        self.handle_regenerate_button()
        # print('placeholder:', placeholder)
        # self.handle_regenerate_button(placeholder)

    def style_main_header(self):
        st.markdown(
            "<h1 style='text-align: center; color: grey;'>🤖 HLS Coder 📝</h1>",
            unsafe_allow_html=True
        )

    def setup_sidebar(self):
        with st.sidebar:
            st.subheader('Models and parameters')
            self.model_list = ['llm']
            self.llm = st.selectbox('Choose a coder model', self.model_list, key='selected_model')
            self.temperature = st.slider('temperature', min_value=0.01, max_value=1.0, value=0.2, step=0.1)
            self.top_p = st.slider('top_p', min_value=0.01, max_value=1.0, value=0.9, step=0.01)
            self.max_length = st.slider('max_length', min_value=64, max_value=2048, value=2048, step=8)
            st.button('Clear Chat History', on_click=self.clear_chat_history)

    def initialize_session_state(self):
        if "messages" not in st.session_state:
            st.session_state.messages = []

    def display_chat_history(self):
        for message in st.session_state.messages:
            with st.chat_message(message["role"]):
                if message["role"] == "assistant":
                    st.code(message["content"], language='c')
                else:
                    st.markdown(message["content"])

    def clear_chat_history(self):
        st.session_state.messages = []
        if 'response_display' in st.session_state:
            st.session_state.response_display.empty()

    def handle_prompt_input(self):
        prompt = st.chat_input()
        if prompt:
            st.session_state.messages.append({"role": "user", "content": prompt})
            with st.chat_message("user"):
                st.markdown(prompt)

            if len(st.session_state.messages) and st.session_state.messages[-1]["role"] != "assistant":
                placeholder = self.generate_and_display_response(prompt)
                return placeholder

    def handle_regenerate_button(self):
        if len(st.session_state.messages) and st.session_state.messages[-1]["role"] == "assistant":
            if st.button("🔄 Regenerate"):
                self.regenerate_response(st.session_state.placeholder)
    def generate_and_display_response(self, prompt_input):
        with st.chat_message("assistant"):
            placeholder = st.empty()
            with st.spinner("Thinking..."):
                # if "response_display" not in st.session_state:
                #     st.session_state.response_display = self.get_placeholder()
                #     st.session_state.block_list.append(st.session_state.response_display)

                full_response = ''
                for item in self.generate_response(prompt_input):
                    full_response += item
                    placeholder.code(full_response, language='c')
                st.session_state.messages.append({"role": "assistant", "content": full_response})
                # print('current block list:', len(st.session_state.block_list))
            return placeholder

    def get_placeholder(self):
        return st.empty()

    def generate_response(self, prompt_input):
        string_dialogue = "Let's think step by step.\n\n"
        for dict_message in st.session_state.messages:
            string_dialogue += dict_message["content"] + "\n\n"
        params = {
            "temperature": self.temperature,
            "top_p": self.top_p,
            "max_length": self.max_length,
            "model": self.llm,
        }
        output = self.request_model(string_dialogue + prompt_input, params=params)
        return output

    def request_model(self, prompt, model="llm", params=None):
        response = self.client.chat.completions.create(
            model=model,
            messages=[{"role": "user", "content": prompt}],
            temperature=params["temperature"],
            max_tokens=params["max_length"],
            top_p=params["top_p"],
            stream=True
        )
        for chunk in response:
            if chunk.choices[0].delta.content:
                yield chunk.choices[0].delta.content

    def regenerate_response(self, placeholder):
        if st.session_state.messages and st.session_state.messages[-1]["role"] == "assistant":
            st.session_state.messages.pop()
            if st.session_state.messages and st.session_state.messages[-1]["role"] == "user":
                last_user_message = st.session_state.messages[-1]["content"]
                placeholder.empty()

                # if len(st.session_state.block_list) > 0:
                #     st.session_state.block_list[-1].empty()
                with st.spinner("Thinking..."):
                    full_response = ''
                    # st.session_state.response_display = self.get_placeholder()
                    placeholder.markdown("Re-triggering the response generation...\n\n")
                    for item in self.generate_response(last_user_message):
                        full_response += item
                        placeholder.code(full_response, language='c')
                    st.session_state.messages.append({"role": "assistant", "content": full_response})


if __name__ == "__main__":
    api_key = 'sk-123'
    base_url = 'http://127.0.0.1:8080/v1'
    app = HLSCoderApp(api_key, base_url)
