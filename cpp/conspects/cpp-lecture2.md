<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>cpp-lecture2</title>
  <link rel="stylesheet" href="https://stackedit.io/style.css" />
</head>

<body class="stackedit">
  <div class="stackedit__html"><h2 id="rvalue-ссылки">rvalue-ссылки</h2>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">struct</span> big_struct <span class="token punctuation">{</span>
	std<span class="token punctuation">:</span><span class="token punctuation">:</span>array<span class="token operator">&lt;</span><span class="token keyword">int</span><span class="token punctuation">,</span> <span class="token number">10</span><span class="token operator">&gt;</span> data<span class="token punctuation">;</span>
<span class="token punctuation">}</span>

<span class="token keyword">void</span> <span class="token function">foo</span><span class="token punctuation">(</span><span class="token keyword">int</span><span class="token punctuation">,</span> <span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">)</span> <span class="token comment">// передаются как обычно, 6 (4,5 в зависимости от компилятора) передаются через регистры, остальные - через стек.</span>

<span class="token keyword">void</span> <span class="token function">foo</span><span class="token punctuation">(</span>big_struct<span class="token punctuation">,</span> <span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">)</span> <span class="token comment">// структура копируется, в ф-ю передаётся ссылка на копию.</span>
</code></pre>
<p>1-ый вариант (в C++):</p>
<pre class=" language-c"><code class="prism ++ language-c">big_struct a<span class="token punctuation">;</span>
<span class="token punctuation">{</span>
big_struct copy <span class="token operator">=</span> a<span class="token punctuation">;</span>
<span class="token function">f</span><span class="token punctuation">(</span>copy<span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>

<span class="token keyword">void</span> <span class="token function">f</span><span class="token punctuation">(</span>big_struct<span class="token operator">&amp;</span><span class="token punctuation">)</span> <span class="token punctuation">{</span> <span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">.</span> <span class="token punctuation">}</span>
</code></pre>
<p>2-ой (в Delphi):</p>
<pre class=" language-c"><code class="prism ++ language-c">big_struct a<span class="token punctuation">;</span>
<span class="token function">f</span><span class="token punctuation">(</span>a<span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">void</span> <span class="token function">f</span><span class="token punctuation">(</span>big_struct <span class="token keyword">const</span><span class="token operator">&amp;</span> a<span class="token punctuation">)</span> <span class="token punctuation">{</span>
	big_struct copy <span class="token operator">=</span> a<span class="token punctuation">;</span>
	<span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">.</span>
<span class="token punctuation">}</span>
</code></pre>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">struct</span> big_struct <span class="token punctuation">{</span>
	std<span class="token punctuation">:</span><span class="token punctuation">:</span>array<span class="token operator">&lt;</span><span class="token keyword">int</span><span class="token punctuation">,</span> <span class="token number">10</span><span class="token operator">&gt;</span> data<span class="token punctuation">;</span>
<span class="token punctuation">}</span><span class="token punctuation">;</span>

big_struct <span class="token function">foo</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
</code></pre>
<p>как возвращается структура:</p>
<pre class=" language-c"><code class="prism ++ language-c">big_struct <span class="token function">f</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">void</span> <span class="token function">g</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
	big_struct a <span class="token operator">=</span> <span class="token function">f</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<p>и это преобразовывается примерно следующим образом:</p>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">void</span> <span class="token function">f</span><span class="token punctuation">(</span>big_struct<span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">void</span> <span class="token function">f</span><span class="token punctuation">(</span><span class="token keyword">void</span><span class="token operator">*</span> result<span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">.</span>
	ctor_ <span class="token function">big_struct</span><span class="token punctuation">(</span>result<span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">// конструктор</span>
<span class="token punctuation">}</span>

<span class="token keyword">void</span> <span class="token function">g</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token keyword">char</span> a_buf<span class="token punctuation">[</span><span class="token keyword">sizeof</span><span class="token punctuation">(</span>big_struct<span class="token punctuation">)</span><span class="token punctuation">]</span><span class="token punctuation">;</span>
	<span class="token function">f</span><span class="token punctuation">(</span>a_buf<span class="token punctuation">)</span><span class="token punctuation">;</span>
	big_struct<span class="token operator">&amp;</span> a <span class="token operator">=</span> <span class="token punctuation">(</span>big_struct<span class="token operator">&amp;</span><span class="token punctuation">)</span>a_buf<span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<ul>
<li>при передаче структуры в функцию не обязательно происходит копирование</li>
<li>аналогично при возвращаемом значении</li>
</ul>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">struct</span> big_struct <span class="token punctuation">{</span>
	<span class="token function">big_struct</span><span class="token punctuation">(</span><span class="token keyword">int</span><span class="token punctuation">,</span> <span class="token keyword">int</span><span class="token punctuation">,</span> <span class="token keyword">int</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span><span class="token punctuation">;</span>

big_struct <span class="token function">g</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">.</span>
	<span class="token keyword">return</span> <span class="token function">big_struct</span><span class="token punctuation">(</span><span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<p>казалось бы, код выше работает следующим образом:</p>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">void</span> <span class="token function">g</span><span class="token punctuation">(</span><span class="token keyword">void</span><span class="token operator">*</span> result<span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token keyword">char</span> tmp<span class="token punctuation">[</span><span class="token keyword">sizeof</span><span class="token punctuation">(</span>big_struct<span class="token punctuation">)</span><span class="token punctuation">]</span><span class="token punctuation">;</span>
	<span class="token function">big_struct_ctor</span><span class="token punctuation">(</span>tmp<span class="token punctuation">,</span> <span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
	<span class="token function">big_struct_ctor</span><span class="token punctuation">(</span>result<span class="token punctuation">,</span> <span class="token punctuation">(</span>big_struct<span class="token operator">&amp;</span><span class="token punctuation">)</span>tmp<span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<p>но зачем делать лишнее копирование?</p>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">void</span> <span class="token function">g</span><span class="token punctuation">(</span><span class="token keyword">void</span><span class="token operator">*</span> result<span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token function">big_struct_ctor</span><span class="token punctuation">(</span>result<span class="token punctuation">,</span> <span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<ul>
<li>это называется <code>return value optimization (RVO)</code></li>
</ul>
<p>тут можно создать переменную на месте <code>return</code></p>
<pre class=" language-c"><code class="prism ++ language-c">big_struct <span class="token function">g</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
	big_struct <span class="token function">tmp</span><span class="token punctuation">(</span><span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
	<span class="token punctuation">.</span><span class="token punctuation">.</span><span class="token punctuation">.</span>
	<span class="token keyword">return</span> tmp<span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<p>а тут уже нет</p>
<pre class=" language-c"><code class="prism ++ language-c">big_struct <span class="token function">g</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
	big_struct <span class="token function">tmp</span><span class="token punctuation">(</span><span class="token number">1</span><span class="token punctuation">,</span> <span class="token number">2</span><span class="token punctuation">,</span> <span class="token number">3</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
	<span class="token keyword">if</span> <span class="token punctuation">(</span>bool<span class="token punctuation">)</span>
		<span class="token keyword">return</span> <span class="token function">big_struct</span><span class="token punctuation">(</span><span class="token number">4</span><span class="token punctuation">,</span> <span class="token number">5</span><span class="token punctuation">,</span> <span class="token number">6</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
	<span class="token keyword">return</span> tmp<span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<ul>
<li>
<p>можем оптимизировать, если известны известны значения возвращаемой переменной во всех ветках</p>
</li>
<li>
<p>при изменении <code>tmp</code> в первом варианте просто изменяем <code>result</code></p>
</li>
<li>
<p>при кидании исключения вызывается деструктор <code>result</code></p>
</li>
<li>
<p>что делать, если хотим хранить вектор некопируемых объектов (например дескрипторы файлов), а на дворе 2003 год?</p>
</li>
<li>
<p>можно хранить ссылки на них, например:<br>
<code>std::vector&lt;file_descriptor*&gt; v;</code></p>
</li>
<li>
<p>или <code>shared_ptr</code> :<br>
<code>std::vector&lt;boost::shared_ptr&lt;file_descriptor&gt;&gt; v;</code></p>
</li>
</ul>
<h2 id="move">move</h2>
<pre class=" language-c"><code class="prism ++ language-c">std<span class="token punctuation">:</span><span class="token punctuation">:</span>vector<span class="token operator">&lt;</span>std<span class="token punctuation">:</span><span class="token punctuation">:</span>string<span class="token operator">&gt;</span> v<span class="token punctuation">;</span>
std<span class="token punctuation">:</span><span class="token punctuation">:</span>string s<span class="token punctuation">;</span>
v<span class="token punctuation">.</span><span class="token function">push_back</span><span class="token punctuation">(</span>s<span class="token punctuation">)</span><span class="token punctuation">;</span>
</code></pre>
<ul>
<li>хотим создать строку, закинуть в вектор и забыть про исходную строку</li>
</ul>
<p><code>&amp;</code> - <code>lvalue</code> ссылки<br>
<code>&amp;&amp;</code> - <code>rvalue</code> ссылки</p>
<p>пример:</p>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">int</span> <span class="token function">f</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">int</span> a <span class="token operator">=</span> <span class="token number">5</span><span class="token punctuation">;</span>
<span class="token keyword">int</span><span class="token operator">&amp;</span> b <span class="token operator">=</span> a<span class="token punctuation">;</span> <span class="token comment">//ok</span>
<span class="token keyword">int</span><span class="token operator">&amp;&amp;</span> c <span class="token operator">=</span> a<span class="token punctuation">;</span> <span class="token comment">//error</span>
<span class="token keyword">int</span><span class="token operator">&amp;</span> d <span class="token operator">=</span> <span class="token function">f</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">//error</span>
<span class="token keyword">int</span><span class="token operator">&amp;&amp;</span> e <span class="token operator">=</span> <span class="token function">f</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">//ok</span>
</code></pre>
<ul>
<li>в <code>c++11</code> добавили возможность перегружать по rvalue-ссылкам:</li>
</ul>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">void</span> <span class="token function">push_back</span><span class="token punctuation">(</span>T <span class="token keyword">const</span><span class="token operator">&amp;</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token keyword">void</span> <span class="token function">push_back</span><span class="token punctuation">(</span>T<span class="token operator">&amp;&amp;</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
</code></pre>
<p><code>string(string const&amp;)</code> - copy constructor<br>
<code>string(string&amp;&amp;)</code> - move constructor</p>
<p><img src="https://i.stack.imgur.com/b2VBV.png" alt="enter image description here"></p>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">void</span> <span class="token function">foo</span><span class="token punctuation">(</span>T<span class="token operator">&amp;&amp;</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token keyword">void</span> <span class="token function">push_back</span><span class="token punctuation">(</span>T<span class="token operator">&amp;&amp;</span> a<span class="token punctuation">)</span> <span class="token punctuation">{</span>
   <span class="token function">foo</span><span class="token punctuation">(</span>a<span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">//не работает, так как a - lvalue</span>
<span class="token punctuation">}</span>
</code></pre>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">void</span> <span class="token function">foo</span><span class="token punctuation">(</span>T<span class="token operator">&amp;&amp;</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token keyword">void</span> <span class="token function">push_back</span><span class="token punctuation">(</span>T<span class="token operator">&amp;&amp;</span> a<span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token function">foo</span><span class="token punctuation">(</span>static_cast<span class="token operator">&lt;</span>T<span class="token operator">&amp;&amp;</span><span class="token operator">&gt;</span><span class="token punctuation">(</span>a<span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">//а так всё норм</span>
<span class="token punctuation">}</span>
</code></pre>
<blockquote>
<p>конструкцию вида <code>static_cast&lt;T&amp;&amp;&gt;</code> приходится писать слишком часто, поэтому запилили следующее:</p>
<pre class=" language-c"><code class="prism ++ language-c">template <span class="token operator">&lt;</span>typename T<span class="token operator">&gt;</span>
T<span class="token operator">&amp;&amp;</span> <span class="token function">move</span><span class="token punctuation">(</span>T<span class="token operator">&amp;</span> obj<span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token keyword">return</span> static_cast<span class="token operator">&lt;</span>T<span class="token operator">&amp;&amp;</span><span class="token operator">&gt;</span><span class="token punctuation">(</span>obj<span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<p>ура, теперь можно писать просто <code>foo(move(a))</code></p>
</blockquote>
<p><strong>типичные ошибки</strong></p>
<pre class=" language-c"><code class="prism ++ language-c">string <span class="token function">foo</span><span class="token punctuation">(</span><span class="token punctuation">)</span> <span class="token punctuation">{</span>
	string res <span class="token operator">=</span> <span class="token string">"hello"</span><span class="token punctuation">;</span>
	res <span class="token operator">+</span><span class="token operator">=</span> <span class="token string">"world"</span><span class="token punctuation">;</span>
	<span class="token keyword">return</span> res<span class="token punctuation">;</span>
	<span class="token comment">// return move(res); // wrong</span>
<span class="token punctuation">}</span>
</code></pre>
<ul>
<li>подавляется <strong>NRVO</strong></li>
</ul>
<pre class=" language-c"><code class="prism ++ language-c">T a<span class="token punctuation">;</span>
T b <span class="token operator">=</span> std<span class="token punctuation">:</span><span class="token punctuation">:</span><span class="token function">move</span><span class="token punctuation">(</span>a<span class="token punctuation">)</span><span class="token punctuation">;</span>
</code></pre>
<ul>
<li>если <code>T</code> не поддерживает rvalue, будет вызван просто copy constructor</li>
</ul>
<blockquote>
<p><code>move</code> - не указ, а подсказка</p>
</blockquote>
<pre class=" language-c"><code class="prism ++ language-c">T<span class="token operator">*</span> new_data <span class="token operator">=</span> operator <span class="token function">new</span><span class="token punctuation">(</span><span class="token keyword">sizeof</span><span class="token punctuation">[</span><span class="token punctuation">]</span><span class="token operator">*</span> new_capacity<span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token keyword">for</span> <span class="token punctuation">(</span>size_t i <span class="token operator">=</span> <span class="token number">0</span><span class="token punctuation">;</span> i <span class="token operator">!=</span> <span class="token function">size</span><span class="token punctuation">(</span><span class="token punctuation">)</span><span class="token punctuation">;</span> i<span class="token operator">++</span><span class="token punctuation">)</span>
	<span class="token function">new</span><span class="token punctuation">(</span><span class="token operator">&amp;</span>new_data<span class="token punctuation">[</span>i<span class="token punctuation">]</span><span class="token punctuation">)</span> <span class="token function">T</span><span class="token punctuation">(</span>std<span class="token punctuation">:</span><span class="token punctuation">:</span><span class="token function">move</span><span class="token punctuation">(</span>old_data<span class="token punctuation">[</span>i<span class="token punctuation">]</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">;</span>
</code></pre>
<ul>
<li>не exception safe:
<ol>
<li><code>T</code> может не иметь move constructor</li>
<li>если <code>move</code> есть и он может бросать исключение, он может не использоваться. Проверяется это через <code>enable_if</code>:<pre class=" language-c"><code class="prism ++ language-c">enable_if<span class="token operator">&lt;</span><span class="token function">noexcept</span><span class="token punctuation">(</span>a <span class="token operator">+</span> b<span class="token punctuation">)</span><span class="token operator">&gt;</span><span class="token punctuation">:</span><span class="token punctuation">:</span>type<span class="token punctuation">;</span>
</code></pre>
</li>
</ol>
</li>
</ul>
<blockquote>
<p>таким образом нужно помечать <code>move constructor</code> как <code>noexcept</code></p>
</blockquote>
<pre class=" language-c"><code class="prism ++ language-c">template<span class="token operator">&lt;</span>typename T<span class="token operator">&gt;</span>
bool operator<span class="token operator">&lt;</span><span class="token punctuation">(</span>vector<span class="token operator">&lt;</span>T<span class="token operator">&gt;</span> <span class="token keyword">const</span><span class="token operator">&amp;</span> lhs<span class="token punctuation">,</span> vector<span class="token operator">&lt;</span>T<span class="token operator">&gt;</span> <span class="token keyword">const</span><span class="token operator">&amp;</span> rhs<span class="token punctuation">)</span> <span class="token function">noexcept</span><span class="token punctuation">(</span>false<span class="token punctuation">)</span><span class="token punctuation">;</span>
</code></pre>
<ul>
<li>в <code>noexcept</code> можно передавать логическое выражение</li>
</ul>
<h3 id="forwarding">forwarding</h3>
<pre class=" language-c"><code class="prism ++ language-c">template<span class="token operator">&lt;</span>typename T<span class="token operator">&gt;</span>
<span class="token keyword">void</span> <span class="token function">g</span><span class="token punctuation">(</span>T <span class="token keyword">const</span><span class="token operator">&amp;</span> a<span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token function">f</span><span class="token punctuation">(</span>a<span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>

template<span class="token operator">&lt;</span>typename T<span class="token operator">&gt;</span>
<span class="token keyword">void</span> <span class="token function">g</span><span class="token punctuation">(</span>T<span class="token operator">&amp;</span> a<span class="token punctuation">)</span> <span class="token punctuation">{</span>
	<span class="token function">f</span><span class="token punctuation">(</span>a<span class="token punctuation">)</span><span class="token punctuation">;</span>
<span class="token punctuation">}</span>
</code></pre>
<ul>
<li>первая реализация плохо, убирается константность. Можно сделать перегрузку (2-ой вариант), но для n аргументов кол-во перегрузок - 2^n.</li>
</ul>
<pre class=" language-c"><code class="prism ++ language-c">template<span class="token operator">&lt;</span>typename T<span class="token operator">&gt;</span>
<span class="token keyword">void</span> <span class="token function">f</span><span class="token punctuation">(</span>T<span class="token operator">&amp;</span><span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token keyword">int</span> a<span class="token punctuation">;</span>
<span class="token keyword">int</span> <span class="token keyword">const</span> b <span class="token operator">=</span> <span class="token number">5</span><span class="token punctuation">;</span>

<span class="token comment">// lvalue</span>
<span class="token function">f</span><span class="token punctuation">(</span>a<span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">// T -&gt; int&amp;</span>
<span class="token function">f</span><span class="token punctuation">(</span>b<span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">// T -&gt; int const&amp;</span>

<span class="token comment">// rvalue</span>
<span class="token function">f</span><span class="token punctuation">(</span><span class="token number">5</span><span class="token punctuation">)</span><span class="token punctuation">;</span> <span class="token comment">// T -&gt; int</span>
</code></pre>
<ul>
<li>сохраняем тип, константность и rvalue/lvalue (<strong>perfect forwarding</strong>)</li>
</ul>
<pre class=" language-c"><code class="prism ++ language-c"><span class="token keyword">typedef</span> <span class="token keyword">int</span><span class="token operator">&amp;</span> foo<span class="token punctuation">;</span>
<span class="token keyword">typedef</span> foo<span class="token operator">&amp;</span> bar<span class="token punctuation">;</span>
</code></pre>
<ul>
<li><code>reference collapsing rule</code> (в c++03) - сжимается до одной ссылки</li>
</ul>
<blockquote>
<p>с появлением rvalue ссылок в C++11 правило расширилось:<br>
<code>&amp; &amp; -&gt; &amp;</code><br>
<code>&amp; &amp;&amp; -&gt; &amp;</code><br>
<code>&amp;&amp; &amp; -&gt; &amp;</code><br>
<code>&amp;&amp; &amp;&amp; -&gt; &amp;&amp;</code></p>
</blockquote>
<ul>
<li>в <code>std</code> есть уже написанный <a href="https://en.cppreference.com/w/cpp/utility/forward"><code>forward</code></a></li>
</ul>
<blockquote>
<p>Written with <a href="https://stackedit.io/">StackEdit</a>.</p>
</blockquote>
</div>
</body>

</html>
