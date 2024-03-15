import time

import openai
import requests

openai.api_key = "sk-"
openai.api_base = "https://chatwithai.icu/v1"


async def get_oai_completion(prompt):
    try:
        response = await openai.ChatCompletion.acreate(
            model="gpt-4-0613",
            # model="gpt-3.5-turbo-0613",
            messages=[
                {"role": "system", "content": "You are a helpful assistant."},
                {
                    "role": "user",
                    "content": prompt

                }

            ],
            max_tokens=768,
            temperature=0.,
            top_p=0.95,
            frequency_penalty=0,
            presence_penalty=0
        )
        res = response["choices"][0]["message"]["content"]

        gpt_output = res
        if 'sorry' in gpt_output.lower() or '<' in gpt_output.lower() or '[' in gpt_output.lower():
            return await get_oai_completion(prompt)
        return gpt_output
    except requests.exceptions.Timeout:
        # Handle the timeout error here
        print("The OpenAI API request timed out. Please try again later.")
        return None
    except openai.error.InvalidRequestError as e:
        # Handle the invalid request error here
        print(f"The OpenAI API request was invalid: {e}")
        return None
    except openai.error.APIError as e:
        if "The operation was timeout" in str(e):
            # Handle the timeout error here
            print("The OpenAI API request timed out. Please try again later.")
            #             time.sleep(3)
            return await get_oai_completion(prompt)
        else:
            # Handle other API errors here
            print(f"The OpenAI API returned an error: {e}")
            return None
    except openai.error.RateLimitError as e:
        return await get_oai_completion(prompt)


async def call_chatgpt(image, semaphore):
    async with semaphore:
        success = False
        re_try_count = 15
        ans = ''
        while not success:
            re_try_count -= 1
            try:
                ans = await get_oai_completion(image)
                success = True
            except Exception as e:
                time.sleep(5)
                print('retry for sample for error', e)
                print('=' * 20)
        if ans is None:
            return await call_chatgpt(image, semaphore)
        return ans.replace('\n', ' ').replace('\r', ' ').replace('\t', ' ')
