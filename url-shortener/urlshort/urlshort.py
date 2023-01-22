from flask import Flask, render_template, request, redirect, url_for, flash, abort, session, jsonify, Blueprint
import json
import os.path
from werkzeug.utils import secure_filename


bp = Blueprint('urlshort', __name__)
app = Flask(__name__)
app.secret_key = 'asdfghjkl123333'
@bp.route('/')
def home():
    if os.path.exists('urls.json')==False:
        session.clear()
    return render_template('home.html', codes=session.keys(), classification=session.values())

@bp.route('/your-url', methods=['GET','POST'])
def your_url():
    if request.method == 'POST':
        urls = {}
        
        if os.path.exists('urls.json'):
            with open('urls.json') as urls_file:
                urls = json.load(urls_file) #load the existing urls.json file into url dictionary
                
        if request.form['code'] in urls.keys():
            flash('That shortname is already been taken. Please enter another alias!')
            return redirect(url_for('urlshort.home'))
        
        if 'url' in request.form.keys():
            urls[request.form['code']] = {'url':request.form['url']}
        else:
            f = request.files['file']
            full_name = request.form['code'] + secure_filename(f.filename)
            f.save('/home/rani/Desktop/url-shortener/urlshort/static/user_files/' + full_name)
            urls[request.form['code']] = {'file':full_name}
            
        with open('urls.json','w') as url_file:
            json.dump(urls, url_file)
            session[request.form['code']] = 'url' in request.form.keys()
        return render_template('your_url.html', code=request.form['code'])
    else:
        return redirect(url_for('urlshort.home'))

@bp.route('/<string:code>')
def go_to_url(code):
    if os.path.exists('urls.json'):
        with open('urls.json') as urls_file:
            urls = json.load(urls_file)
            if code in urls.keys():
                if 'url' in urls[code].keys():
                    return redirect(urls[code]['url'])
                else:
                    return redirect(url_for('static', filename='user_files/'+urls[code]['file']))
    return abort(404)

@bp.errorhandler(404)
def page_not_found(error):
    return render_template('page_not_found.html')

@bp.route('/api')
def session_api():
    return jsonify(list(session.keys()))